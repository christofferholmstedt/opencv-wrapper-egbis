/*
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
            /*
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            */

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

int main(int argc, char **argv) {

    Mat img;
    img = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    if( !img.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }

    char* imageName = argv[1];
    int num_ccs;

    // 1. Convert to native format
    image<rgb> *converted = convertMatToNativeImage(&img);
    // 2. Run egbis algoritm
    image<rgb> *seg = segment_image(converted, 0.5, 500, 200, &num_ccs);
    // 3. Convert back to Mat format
    Mat egbisImage = convertNativeToMat(seg);
    // 4. Present image


    // int num_ccs;
    // image<rgb> *seg = segment_image(image, 0.5, 500, 200, &num_ccs);


            // cout << three_channels[0].at<uchar>(i,j) << endl;
            // You can now access the pixel value with cv::Vec3b
                // cout << image.at<uchar>(i,j) << endl;
                //         " " << img.at<cv::Vec3b>(i,j)[1] << " " <<
                //         img.at<cv::Vec3b>(i,j)[2] << std::endl;

    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    imshow( imageName, img );

    namedWindow( "EGBIS image", CV_WINDOW_AUTOSIZE );
    imshow( "EGBIS image", egbisImage);
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

    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    imshow( "Gray image", gray_image );
*/
    waitKey(0);

/*
  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");
*/

  return 0;
}

