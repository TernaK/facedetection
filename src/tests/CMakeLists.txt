find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${facedetector_SOURCE_DIR/include})

add_executable(config_test config_test.cpp)
target_link_libraries(config_test facedetector ${OpennCV_LIBS})

