cmake_minimum_required(VERSION 2.8)
project(egbis)

if(WIN32)
  # put opencv_world???.dll near the final executable before running
  # which is located at "${OpenCV_DIR}/../bin"
  set(OpenCV_DIR "C:/opencv/build/x64/vc15/lib")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif(WIN32)

find_package(OpenCV REQUIRED)

add_compile_options(-Wall)
if(NOT WIN32)
  add_compile_options(-Wextra -Wpedantic)
endif(NOT WIN32)

file(GLOB SOURCES egbis.cpp egbis/disjoint-set.cpp egbis/misc.cpp egbis/segment-graph.cpp egbis/filter.cpp egbis/segment-image.cpp egbis/imconv.cpp egbis/convolve.cpp)

add_library(egbis SHARED ${SOURCES})
target_link_libraries(egbis ${OpenCV_LIBS})
target_include_directories(egbis PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(main main.cpp)
target_link_libraries(main egbis)
