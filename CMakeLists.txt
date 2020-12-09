cmake_minimum_required(VERSION 2.8)
project(egbis)

find_package(OpenCV REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB SOURCES egbis.cpp egbis/disjoint-set.cpp egbis/misc.cpp egbis/segment-graph.cpp egbis/filter.cpp egbis/segment-image.cpp egbis/imconv.cpp egbis/convolve.cpp)

add_library(egbis SHARED ${SOURCES})
target_link_libraries(egbis ${OpenCV_LIBS})
target_include_directories(egbis PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(main main.cpp)
target_link_libraries(main egbis)

