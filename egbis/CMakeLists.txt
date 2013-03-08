cmake_minimum_required(VERSION 2.8)
project( opencv-wrapper-egbis )
find_package( OpenCV REQUIRED )
add_executable( egbis segment.cpp segment-image.h segment-graph.h disjoint-set.h image.h )
target_link_libraries( egbis ${OpenCV_LIBS} )

