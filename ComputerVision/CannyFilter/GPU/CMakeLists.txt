cmake_minimum_required(VERSION 2.8)
project( Canny_GPU )
find_package( OpenCV REQUIRED )
add_executable( Canny_GPU Canny_GPU.cpp )
target_link_libraries( Canny_GPU ${OpenCV_LIBS} )
