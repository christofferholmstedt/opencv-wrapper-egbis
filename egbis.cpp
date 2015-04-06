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
    image<rgb> *segmentetImage = segment_image(nativeImage, sigma, k, min_size, numccs);
    // 3. Convert back to Mat format
    output = convertNativeToMat(segmentetImage);

    return output;
}
