cmake_minimum_required( VERSION 2.8 )
project( ch8ex10 )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ch8ex10 ch8ex10.cc )
target_link_libraries( ch8ex10 ${OpenCV_LIBS} )
