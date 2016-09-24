/* -*- C++ -*-
 *
 * Copyright (C) 2002 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * MillionVis is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * MillionVis is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MillionVis; see the file COPYING.  If not, write to the
 * Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA. 
 */
#ifndef INFOVIS_DRAWING_LITECOLORCHOOSER_HPP
#define INFOVIS_DRAWING_LITECOLORCHOOSER_HPP

#include <infovis/drawing/lite/LiteBox.hpp>
#include <infovis/drawing/lite/LiteSlider.hpp>

namespace infovis {

class ColorScheme : public BoundedRangeObserver
{
public:
  ColorScheme();

  virtual ColorScheme * clone() const;

  virtual void fillColorRamp(Color * ramp, int size);
  virtual void renderColorValue(const Box& b);

  virtual void setXObservable(BoundedRangeObservable * obs);
  virtual void setYObservable(BoundedRangeObservable * obs);
  virtual void setZObservable(BoundedRangeObservable * obs);

  virtual void valueDragged(BoundedRangeObservable * obs);
  virtual void rangeDragged(BoundedRangeObservable * obs);
  virtual void updateBoundedRange(BoundedRangeObservable * obs);
protected:
  BoundedRangeObservable * x_observable_;
  BoundedRangeObservable * y_observable_;
  BoundedRangeObservable * z_observable_;
  float x_;
  float y_;
  float z_;
};

/**
 * Lite for selecting a color.
 */
class LiteColorSlider : public LiteSlider,
			public virtual gc_cleanup
{
public:
  LiteColorSlider(ColorScheme * scheme,
		  const Box& bounds,
		  direction dir = left_to_right,
		  const Color& fg = color_black,
		  const Color& bg = color_white);
  ~LiteColorSlider();

  virtual Lite * clone() const;
  virtual void renderBackground(const Box& b);
  virtual void renderThumb(const Box& b);
  virtual void fillColors(Color * ramp, int n);
protected:
  unsigned int texture_;
  ColorScheme * scheme_;
};

class LiteColorSurface : public LiteBounded,
			 public BoundedRangeObserver,
			 public Interactor3States,
			 public DefaultBeginEndObservable
{
public:
  LiteColorSurface(ColorScheme * scheme,
		   const Box& bounds,
		   const Color& fg = color_black,
		   const Color& bg = color_white);

  virtual Interactor * interactor(const string& name, int tool_id);
  virtual void doRender(const RenderContext& rc);
  virtual Lite * clone() const;

  virtual BoundedRangeObservable* getXObservable() const;
  virtual void setXObservable(BoundedRangeObservable* v);

  virtual BoundedRangeObservable* getYObservable() const;
  virtual void setYObservable(BoundedRangeObservable* v);
  
  virtual const Color& getForegroundColor() const;
  virtual void setForegroundColor(const Color& color);

  virtual const Color& getBackgroundColor() const;
  virtual void setBackgroundColor(const Color& color);

  virtual float getXValue(const Event& ev) const;
  virtual float getYValue(const Event& ev) const;
  virtual float getZ() const;
  virtual void setZ(float f);

  virtual void renderBackground(const Box& b);
  virtual void renderValue(const Box& b, float x, float y);
  virtual void renderOverlay(const Box& b);

  virtual void valueDragged(BoundedRangeObservable * obs);
  virtual void rangeDragged(BoundedRangeObservable * obs);
  virtual void updateBoundedRange(BoundedRangeObservable * obs);

  // Interactor3States
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);
  virtual void doAbort(const Event& ev);

  virtual void fillColors(Color * surface, int width, int height);
protected:
  BoundedRangeObservable * x_observable_;
  BoundedRangeObservable * y_observable_;
  Color foreground_color_;
  Color background_color_;
  float x_saved_;
  float y_saved_;
  float z_;
  ColorScheme * scheme_;
};

/**
 * Class for chosing a color.
 */
class LiteColorChooser : public LiteGroup,
			 public BoundedRangeObserver
{
public:
  LiteColorChooser();

  Lite * clone() const;
  
protected:
  LiteColorSlider * slider_;
  LiteColorSurface * surface_;
};
  

} // namespace infovis


#endif // INFOVIS_DRAWING_LITECOLORCHOOSER_HPP
