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
#include "egbis.h"
#include <opencv2/opencv.hpp>
#include "egbis/segment-image.h"
#include "egbis/misc.h"
#include "egbis/image.h"

/****
 * OpenCV C++ Wrapper using the Mat class
 ***/
image<rgb>* convertMatToNativeImage(const cv::Mat& input){
    int w = input.cols;
    int h = input.rows;
    image<rgb> *im = new image<rgb>(w,h);

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            rgb curr;
			cv::Vec3b intensity = input.at<cv::Vec3b>(i,j);
            curr.b = intensity.val[0];
            curr.g = intensity.val[1];
            curr.r = intensity.val[2];
            im->data[i*w+j] = curr;
        }
    }
    return im;
}

cv::Mat convertNativeToMat(image<rgb>* input){
    int w = input->width();
    int h = input->height();
	cv::Mat output(cv::Size(w,h),CV_8UC3);

    for(int i =0; i<h; i++){
        for(int j=0; j<w; j++){
            rgb curr = input->data[i*w+j];
            output.at<cv::Vec3b>(i,j)[0] = curr.b;
            output.at<cv::Vec3b>(i,j)[1] = curr.g;
            output.at<cv::Vec3b>(i,j)[2] = curr.r;
        }
    }

    return output;
}

cv::Mat runEgbisOnMat(const cv::Mat& input, float sigma, float k, int min_size, int *numccs) {
    int w = input.cols;
    int h = input.rows;
	cv::Mat output(cv::Size(w,h),CV_8UC3);

    // 1. Convert to native format
    image<rgb> *nativeImage = convertMatToNativeImage(input);
    // 2. Run egbis algoritm
    image<rgb> *segmentedImage = segment_image(nativeImage, sigma, k, min_size, numccs);
    // 3. Convert back to Mat format
    output = convertNativeToMat(segmentedImage);

	delete nativeImage;
	delete segmentedImage;
    return output;
}
