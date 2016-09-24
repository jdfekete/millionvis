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
#ifndef INFOVIS_DRAWING_POINT_VEC_HPP
#define INFOVIS_DRAWING_POINT_VEC_HPP
/*
 * $Id: point_vec.hpp,v 1.11 2002/07/05 23:22:22 fekete Exp $
 *
Copyright (c) 2001 Stephane Conversy, Jean-Daniel Fekete and Ecole des
Mines de Nantes.
All rights reserved.

 */
#include <infovis/alloc.hpp>

namespace infovis {

template <int Dim, class Coord>
struct vector_;

/**
 * Traits for points
 */
template <class Point>
struct point_traits {
  typedef typename Point::coord_type coord_type;
  enum { dimension = Point::dimension };
  typedef typename Point::iterator iterator;
  typedef typename Point::const_iterator const_iterator;
};

/**
 * Basic point data type
 */
template <int Dim, class Coord>
struct point_
{
  typedef Coord coord_type;
  enum { dimension = Dim };
  typedef Coord * iterator;
  typedef const Coord * const_iterator;

#define CFOREACH for (int i = 0; i != Dim; i++)
  
  Coord p[Dim];

  point_() { }			// not initialized automatically

  template <class InputIterator>
  explicit point_(InputIterator s, InputIterator e) {
    for (iterator i = begin(); i != end() && s != e; i++, s++)
      *i = *e;
  }

  template <class Coord2>
  explicit point_(const point_<Dim, Coord2> & p) {
    typename point_<Dim,Coord2>::const_iterator j = p.begin();
    CFOREACH at(i) = *j++;
  }

  template <class Coord2>
  explicit point_(const vector_<Dim,Coord2>& p);

  point_ operator - () const {
    point_ ret;
    CFOREACH ret[i] = -at(i);
    return ret;
  }
  point_ operator + (const vector_<Dim, Coord>& v) const {
    point_ ret;
    CFOREACH ret[i] = at(i) + v[i];
    return ret;
  }
  point_ operator - (const vector_<Dim, Coord>& v) const {
    point_ ret;
    CFOREACH ret[i] = at(i) - v[i];
    return ret;
  }
  vector_<Dim, Coord> operator - (const point_& pt) const {
    vector_<Dim,Coord> ret;
    CFOREACH ret[i] = at(i) - pt[i];
    return ret;
  }
  point_& operator += (const vector_<Dim, Coord>& v) {
    CFOREACH at(i) += v[i];
    return *this;
  }
  point_& operator -= (const vector_<Dim, Coord>& v) {
    CFOREACH at(i) -= v[i];
    return *this;
  }
  bool operator == (const point_& pt) const {
    CFOREACH if (at(i) != pt[i]) return false;
    return true;
  }
  Coord& operator [](int i) { return p[i]; }
  const Coord& operator [](int i) const { return p[i]; }
  Coord& at(int i) { return p[i]; }
  const Coord& at(int i) const { return p[i]; }
  iterator begin() { return p; }
  const_iterator begin() const { return p; }
  iterator end() { return p + Dim; }
  const_iterator end() const { return p + Dim; }
};

/**
 * Basic vector data type
 */
template <int Dim, class Coord>
struct vector_
{
  typedef Coord coord_type;
  enum { dimension = Dim };
  typedef Coord * iterator;
  typedef const Coord * const_iterator;

  Coord v[Dim];

  vector_() { }

  template <class InputIterator>
  explicit vector_(InputIterator s, InputIterator e) {
    for (iterator i = begin(); i != end() && s != e; i++, s++)
      *i = *e;
  }

  template <class Coord2>
  explicit vector_(const vector_<Dim, Coord2> & p) {
    typename vector_<Dim,Coord2>::const_iterator j = p.begin();
    CFOREACH at(i) = *j++;
  }

  template <class Coord2>
  explicit vector_(const point_<Dim,Coord2>& p) {
    CFOREACH v[i] = p[i];
  }

  vector_ operator - () const {
    vector_ ret;
    CFOREACH ret[i] = -at(i);
    return ret;
  }
  vector_ operator + (const vector_& v1) const {
    vector_ ret;
    CFOREACH ret[i] = v[i] + v1[i];
    return ret;
  }
  vector_ operator - (const vector_<Dim, Coord>& v1) const {
    vector_ ret;
    CFOREACH ret[i] = v[i] - v1[i];
    return ret;
  }
  vector_& operator += (const vector_<Dim, Coord>& v1) {
    CFOREACH v[i] += v1[i];
    return *this;
  }
  vector_& operator -= (const vector_& v1) {
    CFOREACH v[i] -= v1[i];
    return *this;
  }
  vector_ operator * (const Coord& s) const {
    vector_ ret;
    CFOREACH ret[i] = v[i] * s ;
    return ret;
  }
  vector_ operator / (const Coord& s) const {
    vector_ ret;
    CFOREACH ret[i] = v[i] / s ;
    return ret;
  }
  vector_ invert() const {
    vector_ ret;
    CFOREACH ret[i] = 1 / v[i];
    return ret;
  }    
  const vector_& operator *= (const Coord& s) const {
    CFOREACH v[i] *= s ;
    return *this;
  }
  const vector_& operator /= (const Coord& s) const {
    CFOREACH v[i] /= s ;
    return *this;
  }
  const vector_& self_invert() const {
    CFOREACH v[i] = 1 / v[i];
    return *this;
  }    
  bool operator == (const vector_& v1) const {
    CFOREACH if (v[i] != v1[i]) return false;
    return true;
  }
  const Coord& operator [](int i) const { return v[i]; }
  Coord& operator [](int i) { return v[i]; }
  const Coord& at(int i) const { return v[i]; }
  Coord& at(int i) { return v[i]; }
  iterator begin() { return v; }
  const_iterator begin() const { return v; }
  iterator end() { return v + Dim; }
  const_iterator end() const { return v + Dim; }
};

template <int Dim, class Coord>
inline Coord norm2(const vector_<Dim, Coord>& ve)
{
  Coord c = 0;
  CFOREACH { c += v[i]*v[i]; }
  return c;
}

#undef CFOREACH

} // namespace infovis

#endif
