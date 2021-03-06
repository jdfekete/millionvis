/* -*- C++ -*-
 *
 * Copyright (C) 2016 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef INFOVIS_DRAWING_LITE_GROUP_HPP
#define INFOVIS_DRAWING_LITE_GROUP_HPP

#include <infovis/drawing/lite/LiteBounded.hpp>

namespace infovis {

/**
 * Lite that manages a list of sub-lites.
 */
class LiteGroup : public LiteBounded
{
public:
  LiteGroup();
  LiteGroup(const Box& b);
  virtual ~LiteGroup();

  virtual void setPosition(const Point& p);
  virtual Lite * clone() const;
  virtual int childCount() const;
  virtual Lite * getChild(int index) const;
  virtual void setChild(int index, Lite * l);
  virtual void addChild(Lite *);
  virtual void insertChild(int pos, Lite *);
  virtual void eraseChild(int pos);
  virtual iterator begin();
  virtual const_iterator begin() const;
  virtual iterator end();
  virtual const_iterator end() const;

  virtual bool isFixed() const;
  virtual void setFixed(bool f);
protected:
  virtual void computeBounds();
  List group_;
  bool is_fixed_;
};
  
} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_GROUP_HPP
