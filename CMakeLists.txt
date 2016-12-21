cmake_minimum_required(VERSION 2.6)

project(facedetection)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_definitions(-DSUPPORT_PATH="${facedetection_SOURCE_DIR}/src/support/")
add_definitions(-DTEST_IMAGES_PATH="${facedetection_SOURCE_DIR}/src/tests/test_images/")

add_subdirectory(src)
