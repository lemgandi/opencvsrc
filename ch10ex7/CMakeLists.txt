cmake_minimum_required( VERSION 2.8 )
project( ch10ex7 )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ch10ex7 ch10ex7.cc )
target_link_libraries( ch10ex7 ${OpenCV_LIBS} )
