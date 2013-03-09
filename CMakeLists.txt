cmake_minimum_required(VERSION 2.8)
project( OCVE )

# Add the EGBIS algortihm
# add_subdirectory(egbis)

find_package( OpenCV REQUIRED )
add_executable( main main.cpp  egbis/segment-image.h egbis/segment-graph.h egbis/disjoint-set.h egbis/image.h)
target_link_libraries( main ${OpenCV_LIBS} )

