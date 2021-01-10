/*
Copyright (C) 2015 Yasutomo Kawanishi
Copyright (C) 2013 Christoffer Holmstedt
Copyright (C) 2010 Salik Syed
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
#ifndef EGBIS_H
#define EGBIS_H
#include <opencv2/core.hpp>
#include "egbis/image.h"
#include "egbis/misc.h"

/****
 * OpenCV C++ Wrapper using the Mat class
 ***/
cv::Mat runEgbisOnMat(const cv::Mat& input, float sigma, float k, int min_size, int *numccs);
image<rgb>* convertMatToNativeImage(const cv::Mat& input);
cv::Mat convertNativeToMat(image<rgb>* input);
#endif
