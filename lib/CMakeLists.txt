cmake_minimum_required( VERSION 2.8 )
project( %PROGRAM% )
set(CMAKE_PREFIX_PATH "../../compiled/" FORCE)
find_package ( OpenCV 3.4 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ../include )
add_library(utility STATIC imageWindow.cc utility.cc)

