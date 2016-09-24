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
#ifndef INFOVIS_DRAWING_LITE_LITEENTERLEAVE_HPP
#define INFOVIS_DRAWING_LITE_LITEENTERLEAVE_HPP

#include <infovis/drawing/inter/InteractorEnterLeave.hpp>
#include <infovis/drawing/lite/LiteProxy.hpp>

namespace infovis {

/**
 * Lite that reacts with enter and leave events.
 */
class LiteEnterLeave : public LiteProxy,
		       public InteractorEnterLeave
{
public:
  LiteEnterLeave(Lite * l);
  
  virtual Lite * clone() const;
  virtual Interactor * interactor(const string& name, int toolid);

  //  virtual bool doEnter(const Event& ev);
  //  virtual void doLeave(const Event& ev);

};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITE_LITEENTERLEAVE_HPP