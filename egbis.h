#ifndef EGBIS_H
#define EGBIS_H
#include <opencv2/opencv.hpp>

/****
 * OpenCV C++ Wrapper using the Mat class
 ***/
cv::Mat runEgbisOnMat(const cv::Mat& input, float sigma, float k, int min_size, int *numccs);
#endif
