find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${facedetector_SOURCE_DIR}/include)

file(GLOB facedetector_SRCFILES "*.cpp" "*.c")
file(GLOB facedetector_INCLUDEFILES "*.hpp" "*.h")

set(facedetector_SOURCES ${facedetector_SRCFILES})
set(facedetector_HEADERS ${facedetector_INCLUDEFILES})
#please revide the previous two lines with regards to the next line
add_library(facedetector SHARED ${facedetector_SOURCES} ${facedetector_HEADERS})
target_link_libraries(facedetector ${Opencv_LIBS})

install(TARGETS facedetector DESTINATION lib)
install(FILES ${facedetector_HEADERS} DESTINATION include)

add_subdirectory(samples)
