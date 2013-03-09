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

/*
image<rgb>* convertMatToNativeImage(Mat *input){
    int w = input->cols;
    int h = input->rows;
    image<rgb> *im = new image<rgb>(w,h);
    for(int i =0; i<w; i++){
        for(int j=0; j<h; j++){
            CvScalar s = cvGet2D(input,j,i);
            rgb curr;
            curr.r = s.val[0];
            curr.g = s.val[1];
            curr.b = s.val[2];
            im->data[i+j*w] = curr;
        }
    }
    return im;
}
*/
int main(int argc, char **argv) {

    char* imageName = argv[1];

    Mat image;
    image = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    // 1. Convert to native format
    // image<rgb> *converted = convertMatToNativeImage(&image);
    // 2. Run egbis algoritm
    // 3. Convert back to Mat format
    // 4. Present image

    if( !image.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }

    // int num_ccs;
    // image<rgb> *seg = segment_image(image, 0.5, 500, 200, &num_ccs);
/*
    for(int i=0; i<image.rows; i++)
    {
        for(int j=0; j<image.cols; j++)
        {
            Vec3b intensity = image.at<Vec3b>(i,j);
                uchar blue = intensity.val[0];
                uchar green = intensity.val[1];
                uchar red = intensity.val[2];
        }
    }
*/
            // cout << three_channels[0].at<uchar>(i,j) << endl;
            // You can now access the pixel value with cv::Vec3b
                // cout << image.at<uchar>(i,j) << endl;
                //         " " << img.at<cv::Vec3b>(i,j)[1] << " " <<
                //         img.at<cv::Vec3b>(i,j)[2] << std::endl;

    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    imshow( imageName, image );
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

