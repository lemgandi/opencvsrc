cmake_minimum_required( VERSION 2.8 )
project( ch7ex2 )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ch7ex2 ch7ex2.cc )
target_link_libraries( ch7ex2 ${OpenCV_LIBS} )
