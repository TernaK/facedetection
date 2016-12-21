find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${facedetection_SOURCE_DIR}/include)

file(GLOB facedetection_SRCFILES "*.cpp" "*.c")
file(GLOB facedetection_INCLUDEFILES "*.hpp" "*.h")

set(facedetection_SOURCES ${facedetection_SRCFILES})
set(facedetection_HEADERS ${facedetection_INCLUDEFILES})
#please revide the previous two lines with regards to the next line
add_library(facedetection SHARED ${facedetection_SOURCES} ${facedetection_HEADERS})
target_link_libraries(facedetection ${Opencv_LIBRARIES} opencv_objdetect)

install(TARGETS facedetection DESTINATION lib)
install(FILES ${facedetection_HEADERS} DESTINATION include)

add_subdirectory(samples)
add_subdirectory(tests)
