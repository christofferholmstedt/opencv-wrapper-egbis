OpenCV wrapper for the "egbis" segmentation algorithm
=====================================================
OpenCV wrapper for Efficient Graph-Based Image Segmentation algorithm developed
by Pedro F. Felzenszwalb and Daniel P. Huttenlocher. This is done as a part of my report about using the Efficient
Graph-Based Image segmentation method to detect roads from Bing maps.

* [My project report here on
  Github](https://github.com/christofferholmstedt/maa507-report-mathematics-behind-internet)
* [Efficient Graph-Based Image Segmentation
  algorithm (implementation of the algorithm)](http://cs.brown.edu/~pff/segment/) (I recommend reading the paper)
* [Salik Syed - C and IplImage wrapper for OpenCV](https://github.com/saliksyed/OpenCVGraphSegmentation)

TODO
----
* Move algorithm wrapper to separate file so it can be used outside of the
  example application.
* Move interface/gui code out of main.cpp.

How to use
----------
This program is tested to work on Ubuntu 12.04 LTS with cmake from ubuntu
repository and OpenCV compiled from source with Qt support.
### Version 2.0.0
##### OpenCV wrapper Example
[Tag
v2.0.0](https://github.com/christofferholmstedt/opencv-wrapper-egbis/tree/v2.0.0)

The root directory in this version has an example using the OpenCV wrapper
inside main.cpp. To build and run it do the following:

    **To build**
    cd <project_root_directory>/
    mkdir build
    cd build/
    cmake ../
    make

    **To run**
    ./main ../images/lulea1.ppm

This will open the OpenCV highgui/Qt interface for two images. The original
in color and a segmentet image in the other one. The segmentet image can
be save using the "Save" trackbar.
