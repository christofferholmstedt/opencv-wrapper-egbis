#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        cout << " Usage: display_image ImageToLoadAndDisplay \n " << endl;
        return -1;
    }

    char* imageName = argv[1];

    Mat image;
    image = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    if( !image.data )
    {
        cout << "Could not open or find the image." << std::endl;
        return -1;
    }

    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );

    imwrite( "../../images/tempImage.jpg", gray_image );

    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    imshow( imageName, image );
    imshow( "Gray image", gray_image );

    waitKey(0);

    return 0;
}
