find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${facedetector_SOURCE_DIR/include})

add_executable(image_detection image_detection.cpp)
target_link_libraries(image_detection facedetector ${OpennCV_LIBS})

