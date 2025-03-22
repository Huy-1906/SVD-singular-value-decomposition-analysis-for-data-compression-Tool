cmake_minimum_required(VERSION 3.10)
project(SVD_Compression)

find_package(OpenCV REQUIRED)

add_executable(svd_compression svd_compression.c)
target_link_libraries(svd_compression ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})
