cmake_minimum_required(VERSION 2.8)
project( Canny )
find_package( OpenCV REQUIRED )
add_executable( Canny Canny.cpp )
target_link_libraries( Canny ${OpenCV_LIBS} )
