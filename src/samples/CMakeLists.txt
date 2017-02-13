find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(dlib REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${facedetection_SOURCE_DIR/include})

add_executable(image_detection image_detection.cpp)
target_link_libraries(image_detection facedetection ${OpennCV_LIBS} ${Boost_LIBS})

add_executable(face_landmark_detection_ex face_landmark_detection_ex.cpp)
target_link_libraries(face_landmark_detection_ex ${dlib_LIBS} ${OpenCV_LIBS})
