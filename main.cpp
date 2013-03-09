/*
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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "egbis/image.h"
#include "egbis/misc.h"
#include "egbis/pnmfile.h"
#include "egbis/segment-image.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


image<rgb>* convertMatToNativeImage(Mat *input){
    int w = input->cols;
    int h = input->rows;
    image<rgb> *im = new image<rgb>(w,h);

    for(int i=0; i<input->rows; i++)
    {
        for(int j=0; j<input->cols; j++)
        {
            rgb curr;
            Vec3b intensity = input->at<Vec3b>(i,j);
            curr.b = intensity.val[0];
            curr.g = intensity.val[1];
            curr.r = intensity.val[2];
            im->data[i+j*w] = curr;
        }
    }
    return im;
}

Mat convertNativeToMat(image<rgb>* input){
    int w = input->width();
    int h = input->height();
    Mat output(Size(w,h),CV_8UC3);

    for(int i =0; i<w; i++){
        for(int j=0; j<h; j++){
            rgb curr = input->data[i+j*w];
            output.at<Vec3b>(i,j)[0] = curr.b;
            output.at<Vec3b>(i,j)[1] = curr.g;
            output.at<Vec3b>(i,j)[2] = curr.r;
        }
    }

    return output;
}

Mat runEgbisOnMat(Mat *input, float sigma, float k, int min_size, int *numccs) {
    int w = input->cols;
    int h = input->rows;
    Mat output(Size(w,h),CV_8UC3);

    // 1. Convert to native format
    image<rgb> *converted = convertMatToNativeImage(input);
    // 2. Run egbis algoritm
    image<rgb> *seg = segment_image(converted, sigma, k, min_size, numccs);
    // 3. Convert back to Mat format
    output = convertNativeToMat(seg);

    return output;
}

Mat egbisImage;
Mat img;
char* imageName;
int num_ccs;
int sigma_switch_value = 1;
int sigma_switch_high = 10;
int k_switch_value = 3;
int k_switch_high = 5;

void switch_callback_sigma( int position ){
    sigma_switch_value = position;
    float sigma_value;

    switch (sigma_switch_value) {
        case 0:
            sigma_value = 0;
            break;
        case 1:
            sigma_value = 0.1;
            break;
        case 2:
            sigma_value = 0.2;
            break;
        case 3:
            sigma_value = 0.3;
            break;
        case 4:
            sigma_value = 0.4;
            break;
        case 5:
            sigma_value = 0.5;
            break;
        case 6:
            sigma_value = 0.6;
            break;
        case 7:
            sigma_value = 0.7;
            break;
        case 8:
            sigma_value = 0.8;
            break;
        case 9:
            sigma_value = 0.9;
            break;
        case 10:
            sigma_value = 1;
            break;
    }
    egbisImage = runEgbisOnMat(&img, sigma_value, 500, 200, &num_ccs);

    // 4. Present image
    imshow( "EGBIS", egbisImage);
}

void switch_callback_k( int position ){
    k_switch_value = position;
}

int main(int argc, char **argv) {

    img = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    if( !img.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }


    imageName = argv[1];
    egbisImage = runEgbisOnMat(&img, 0.5, 500, 200, &num_ccs);

    // 4. Present image
    namedWindow( imageName , CV_WINDOW_AUTOSIZE );
    imshow( imageName , img );

    cvCreateTrackbar("Sigma",imageName, &sigma_switch_value, sigma_switch_high, switch_callback_sigma);

    namedWindow( "EGBIS", CV_WINDOW_AUTOSIZE );
    imshow( "EGBIS", egbisImage);
/*
    float sigma = atof(argv[1]);
    float k = atof(argv[2]);
    int min_size = atoi(argv[3]);

    printf("loading input image.\n");
    image<rgb> *input = loadPPM(argv[4]);

    printf("processing\n");
    int num_ccs;
    image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs);
    savePPM(seg, argv[5]);

    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );
    imwrite( "../../images/tempImage.jpg", gray_image );
*/
    waitKey(0);

  return 0;
}

