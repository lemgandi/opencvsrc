cmake_minimum_required( VERSION 2.8 )
project( divide_colors )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( divide_colors divide_colors.cc )
target_link_libraries( divide_colors ${OpenCV_LIBS} )
