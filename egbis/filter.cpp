/*
Copyright (C) 2015 Yasutomo Kawanishi
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

/* simple filters */

#include "filter.h"

void normalize(std::vector<float> &mask) {
  size_t len = mask.size();
  float sum = 0;
  for (size_t i = 1; i < len; i++) {
    sum += fabs(mask[i]);
  }
  sum = 2*sum + fabs(mask[0]);
  for (size_t i = 0; i < len; i++) {
    mask[i] /= sum;
  }
}

std::vector<float> make_fgauss(float sigma)
{
  sigma = std::max(sigma, 0.01F);
  int len = (int)ceil(sigma * WIDTH) + 1;
  std::vector<float> mask(len);
  for (int i = 0; i < len; i++)
  {
    mask[i] = static_cast<float>(exp(-0.5 * square(i / sigma)));
  }
  return mask;
}

/* convolve image with gaussian filter */

image<float> *smooth(image<float> *src, float sigma) {
  std::vector<float> mask = make_fgauss(sigma);
  normalize(mask);

  image<float> *tmp = new image<float>(src->height(), src->width(), false);
  image<float> *dst = new image<float>(src->width(), src->height(), false);
  convolve_even(src, tmp, mask);
  convolve_even(tmp, dst, mask);

  delete tmp;
  return dst;
}


image<float> *smooth(image<uchar> *src, float sigma) {
  image<float> *tmp = imageUCHARtoFLOAT(src);
  image<float> *dst = smooth(tmp, sigma);
  delete tmp;
  return dst;
}

