find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${facedetection_SOURCE_DIR/include})

add_executable(image_detection image_detection.cpp)
target_link_libraries(image_detection facedetection ${OpennCV_LIBS})

