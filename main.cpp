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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "egbis.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


/****
 * END OF: OpenCV C++ Wrapper using the Mat class
 ***/

Mat egbisImage;
Mat img;
char* imageName;
int num_ccs;

/****
 * GUI related variables and functions (trackBars/Sliders).
 * TODO: Move this to separate file.
 ***/

int sigma_switch_value = 1;
int sigma_switch_high = 30;
int k_switch_value = 500;
int k_switch_high = 5000;
int c_switch_value = 200;
int c_switch_high = 5000;
int run_switch_value = 0;
int run_switch_high = 1;
int save_switch_value = 0;
int save_switch_high = 1;

float sigma_value;

void switch_callback_sigma( int position ){
    sigma_switch_value = position;

    sigma_value = (float)sigma_switch_value/10;
/*
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
*/
}

void switch_callback_k( int position ){
    k_switch_value = position;
}

void switch_callback_c( int position ){
    c_switch_value = position;
}

void switch_callback_save( int position ){

    if (position == 1)
    {
        // TODO: Add variables sigma, k and c to filename
        // so multiple images can be saved.
        imwrite( "../images/egbisImage.jpg", egbisImage);
        c_switch_value = 0;
    }
}

void switch_callback_run( int position ){

    if (position == 1)
    {
        // Calculate new EGBIS segmentation
        // (Mat *input, float sigma, float k, int min_size, int *numccs) {
        egbisImage = runEgbisOnMat(img, sigma_value, (float)k_switch_value, (float)c_switch_value, &num_ccs);
        // Change image shown
        imshow( "EGBIS", egbisImage);
        run_switch_value = 0;

        // TODO: Fix this, it doesn't work as intended.
        // http://docs.opencv.org/modules/highgui/doc/user_interface.html#settrackbarpos
        setTrackbarPos("Run", "EGBIS", run_switch_value);
    }
}

/****
 * END OF: GUI related variables and functions (trackBars/Sliders).
 ***/

/****
 * Main
 ***/
int main(int argc, char **argv) {

    img = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    if( !img.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }


    imageName = argv[1];
    // Create the first EGBIS version with standard values.
    // TODO: Set this input values to match the ones define in global scope
    egbisImage = runEgbisOnMat(img, 0.5, 500, 200, &num_ccs);

    // 4. Present image
    namedWindow( imageName , CV_WINDOW_AUTOSIZE );
    imshow( imageName , img );

    // TODO: Change to C++ method
    // http://docs.opencv.org/modules/highgui/doc/user_interface.html#createtrackbar
    cvCreateTrackbar("Sigma [x/10]",imageName, &sigma_switch_value, sigma_switch_high, switch_callback_sigma);
    cvCreateTrackbar("k",imageName, &k_switch_value, k_switch_high, switch_callback_k);
    cvCreateTrackbar("c",imageName, &c_switch_value, c_switch_high, switch_callback_c);
    cvCreateTrackbar("Run",imageName, &run_switch_value, run_switch_high, switch_callback_run);
    cvCreateTrackbar("Save EGBIS image",imageName, &save_switch_value, save_switch_high, switch_callback_save);

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

/****
 * END OF: Main
 ***/
