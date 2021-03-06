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
#ifndef INFOVIS_DRAWING_COLORS_UVY_HPP
#define INFOVIS_DRAWING_COLORS_UVY_HPP

#include <infovis/drawing/color.hpp>
#include <infovis/drawing/colors/xyz.hpp>

namespace infovis {

struct color_space_uvY {
  enum channel_name { u_prime, v_prime, Y, last_channel };
};

struct color_uvY : public color_type<float, color_space_uvY>
{
  typedef color_type<float, color_space_uvY> super;

  color_uvY();
  color_uvY(float val) : super(val) {}
  color_uvY(const color_uvY& r) {
    for (int chan = 0; chan < last_channel; chan++) {
      channel[chan] = r.channel[chan];
    }
  }
  template <class ChannelIt>
  color_uvY(ChannelIt start, ChannelIt end) {
    int chan;
    for (chan = 0; chan < last_channel; chan++) {
      if (start != end)
	channel[chan] = *start++;
    }
    while(chan < last_channel)
      channel[chan++] = float(0);
  }
  color_uvY(const float& u, const float& v, const float& y) {
    channel[u_prime] = u;
    channel[v_prime] = v;
    channel[Y] = y;
  }
  color_uvY(double u, double v, double y) {
    detail::round(channel[u_prime], u * super::one());
    detail::round(channel[v_prime], v * super::one());
    detail::round(channel[Y], y * super::one());
  }
};

void convert(color_xyz& xyz, const color_uvY& uvY);
void convert(color_uvY& uvY, const color_xyz& xyz);

} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_UVY_HPP
