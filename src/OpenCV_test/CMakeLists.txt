cmake_minimum_required(VERSION 2.8.9)
# 显式设置CMP0048策略为NEW
cmake_policy(SET CMP0048 NEW)
project(opencv_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



find_package(OpenCV REQUIRED)
FILE(GLOB_RECURSE ALL_SOURCE_FILES "*.cc *.cpp")

add_executable(clamp_spline clamp_spline.cc)
target_link_libraries(clamp_spline ${OpenCV_LIBS})

add_executable(arc_draw arc_draw.cc)
target_link_libraries(arc_draw ${OpenCV_LIBS})


