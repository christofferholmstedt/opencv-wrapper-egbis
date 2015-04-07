OpenCV wrapper for the "egbis" segmentation algorithm
=====================================================
OpenCV wrapper for Efficient Graph-Based Image Segmentation algorithm developed
by Pedro F. Felzenszwalb and Daniel P. Huttenlocher. This is done as a part of
my report about using the Efficient Graph-Based Image segmentation method to
detect roads from Bing maps.

* [My project report here on
  Github](https://github.com/christofferholmstedt/maa507-report-mathematics-behind-internet)
* [Efficient Graph-Based Image Segmentation
  algorithm (implementation of the algorithm)](http://cs.brown.edu/~pff/segment/) (I recommend reading the paper)
* [Salik Syed - C and IplImage wrapper for OpenCV](https://github.com/saliksyed/OpenCVGraphSegmentation)

How to use
----------
This program is tested to work on Ubuntu 14.04.2 LTS with cmake from Ubuntu
repository and OpenCV compiled from source with Qt support.

### Clone and compile OpenCV 2.4.9 for Ubuntu 14.04
* [Instructions found at Samontab](http://www.samontab.com/web/2014/06/installing-opencv-2-4-9-in-ubuntu-14-04-lts/)

```
# General Ubuntu OS update
sudo apt-get update
sudo apt-get upgrade

# Install some required applications (1GB+)
# Depending on what features you want you can remove some of this, e.g. texlive
sudo apt-get install build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev \
libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev \
libeigen3-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev \
libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev \
libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev \
libavcodec-dev libavformat-dev libswscale-dev default-jdk ant libvtk5-qt4-dev
```

```
# Download and compile OpenCV
git clone https://github.com/Itseez/opencv
git checkout -b temp_branch 2.4.9

mkdir build
cd build

# Configure OpenCV build settings
# Some of this can be removed depending on what features you want
cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D \
INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D \
WITH_QT=ON -D WITH_OPENGL=ON -D WITH_VTK=ON ../

# Use "make -j4" to use 4 threads when compiling but can cause gcc internal errors
# when compiling OpenCV
make
sudo make install

# Configure OpenCV
sudo vim /etc/ld.so.conf.d/opencv.conf
Add "/usr/local/lib" to the possibly empty file.

sudo ldconfig
sudo gedit /etc/bash.bashrc

# Add the following to the bash.bashrc file:
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH

Reboot your computer (logout and login is probably enough)
```
### Git master HEAD
Use same procedure as described below for tag v2.0.0

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
