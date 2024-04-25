project(Bezier_path)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")


find_package(Eigen3 REQUIRED) 
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(bezier_arc_parameterized_node bezier_arc_parameterized.cc)
target_link_libraries(bezier_arc_parameterized_node Eigen3::Eigen ${OpenCV_LIBS})



