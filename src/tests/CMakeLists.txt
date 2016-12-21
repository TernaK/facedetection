find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${facedetection_SOURCE_DIR/include})

add_executable(facedetection_test facedetection_test.cpp)
target_link_libraries(facedetection_test)
