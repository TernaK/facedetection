find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${facedetection_SOURCE_DIR/include})

add_executable(image_detection image_detection.cpp)
target_link_libraries(image_detection facedetection ${OpennCV_LIBS} ${Boost_LIBS})

add_executable(video_tracking video_tracking.cpp)
target_link_libraries(video_tracking facedetection ${OpennCV_LIBS} ${Boost_LIBS})