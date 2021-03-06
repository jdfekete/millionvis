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
#ifndef INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP
#define INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <infovis/drawing/box.hpp>

namespace infovis {

template <class Tree, class Box, 
	  class BorderDrawer = border_drawer<Tree,Box> >
class pick_drawer : public null_drawer<Tree,Box>
{
protected:
  typedef typename box_traits<Box>::coord_type coord_type;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;

  coord_type x, y;
  node_descriptor picked;
  int picked_depth;
  BorderDrawer border;
public:
  pick_drawer(coord_type X, coord_type Y)
    : x(X), y(Y), picked_depth(-1) {}
  pick_drawer()
    : x(0), y(0), picked_depth(-1) {}

  void start() { picked_depth=-1; }
  void finish() { }

  void reset(coord_type X, coord_type Y) { x=X; y=Y; }

  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
    if (! inside(b, x, y))
      return false;
    if (int(depth) <= picked_depth)
      return false;
    picked = n;
    picked_depth = depth;
    return true;
  }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) { }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    if (border.begin_border(b, n, depth)) {
      border.remaining_box(b, n, depth);
    }
  }
  void remove_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    draw_border(b, n, depth);
  }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) { }

  node_descriptor picked_node() const { return picked; }
  bool has_picked() const { return picked_depth != -1; }
};

} // namespace infovis


#endif // INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP
