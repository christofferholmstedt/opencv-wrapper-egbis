cmake_minimum_required(VERSION 2.8)
project( OpenCVWrapperEGBIS )
find_package( OpenCV REQUIRED )
add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )

