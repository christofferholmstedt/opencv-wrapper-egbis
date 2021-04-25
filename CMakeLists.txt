cmake_minimum_required(VERSION 2.8)
project(egbis)

if(WIN32)
  # put opencv_world???.dll near the final executable before running
  # which is located at "${OpenCV_DIR}/../bin"
  # or add "${OpenCV_DIR}/../bin" to PATH environment variable
  # cmake -D OpenCV_DIR="C:/opencv/build/x64/vc15" ..
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif(WIN32)

find_package(OpenCV REQUIRED)

if(WIN32 AND NOT BUILD_SHARED_LIBS)
  # MSVC settings for static build
  # https://stackoverflow.com/a/14172871/12447766
  set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
    )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif(WIN32 AND NOT BUILD_SHARED_LIBS)

set(CMAKE_CXX_STANDARD 11)
if(NOT WIN32)
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_options(-pthread)
endif(NOT WIN32)

file(GLOB SOURCES
  egbis.cpp
  egbis/disjoint-set.cpp
  egbis/misc.cpp
  egbis/segment-graph.cpp
  egbis/filter.cpp
  egbis/segment-image.cpp
  egbis/imconv.cpp
  egbis/convolve.cpp
)

if(WIN32)
  add_library(egbis_library STATIC ${SOURCES})
else(WIN32)
  add_library(egbis_library SHARED ${SOURCES})
endif(WIN32)
target_link_libraries(egbis_library ${OpenCV_LIBS})
target_include_directories(egbis_library PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(main main.cpp)
target_link_libraries(main egbis_library)
