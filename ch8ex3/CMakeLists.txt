cmake_minimum_required( VERSION 2.8 )
project( ch8ex3 )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ch8ex3 ch8ex3.cc )
target_link_libraries( ch8ex3 ${OpenCV_LIBS} )
