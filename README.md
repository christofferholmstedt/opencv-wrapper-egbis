OpenCV wrapper for the "egbis" segmentation algorithm
=====================================================
OpenCV wrapper for Efficient Graph-Based Image Segmentation algorithm developed
by Pedro F. Felzenszwalb and Daniel P. Huttenlocher. This is done as a part of my report about using the Efficient
Graph-Based Image segmentation method to detect roads from Bing maps.

* [My project report here on
  Github](https://github.com/christofferholmstedt/maa507-report-mathematics-behind-internet)
* [Efficient Graph-Based Image Segmentation
  algorithm](http://cs.brown.edu/~pff/segment/) (I recommend reading the paper)


How to use
----------
This program is tested to work on Ubuntu 12.04 LTS with OpenCV compiled from
source with Qt support.

### Version 1.0.0
##### OpenCV example
[Tag 1.0.0](https://github.com/christofferholmstedt/opencv-wrapper-egbis/tags)

The root directory in version 1.0.0 has an example OpenCV program from one of
the tutorials in the documentation. To build and run it do the following:

    To build:
    cd <project_root_directory>
    mkdir build
    cd build/
    cmake ../
    make

    To run:
    ./main ../images/lulea1.ppm

This will open the OpenCV highgui/Qt interface for two images. The original
in color and a gray scale copy of it.

##### Efficient Graph-Based Image Segmentation with CMake
In the egbis folder the original source code from Pedro F. Felzenszwalb is
available with a CMakeLists.txt file to make it possible to generate build
files with CMake.

    To build:
    cd <project_root_directory/egbis/>
    mkdir build
    cd build/
    cmake ../
    make

    To run:
    ./egbis 0.5 500 200 ../../images/lulea1.ppm lulea1-output.ppm

This will generate "lulea1-output.ppm" in the current build directory. The
image is an segmentation of the original image.
