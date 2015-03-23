cmake_minimum_required(VERSION 2.8)
project( OCVE )

# Add the EGBIS algortihm
# add_subdirectory(egbis)

find_package( OpenCV REQUIRED )
add_executable( main main.cpp egbis.h egbis.cpp egbis/segment-image.cpp egbis/segment-image.h egbis/segment-graph.cpp egbis/segment-graph.h egbis/disjoint-set.cpp egbis/disjoint-set.h egbis/image.h egbis/filter.cpp egbis/filter.h egbis/misc.cpp egbis/misc.h)
target_link_libraries( main ${OpenCV_LIBS} )

