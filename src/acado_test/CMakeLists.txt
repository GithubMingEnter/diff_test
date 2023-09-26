cmake_minimum_required(VERSION 2.8.9)
project(acado_test)

# 添加编译选项
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 ${FLAG_OPENMP} -std=c++11")

# 生成compile_commands.json文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 设置可执行文件存放位置
# set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
# 增加cmake模块的检索路径
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
# Prerequisites
find_package(ACADO REQUIRED)
# 头文件路径
include_directories(src ${ACADO_INCLUDE_DIRS})
message("${ACADO_INCLUDE_DIRS}")
# 管理源文件
set(SRC_LIST acado_test.cc)
# 生成可执行文件，名字为result
add_executable(acado_test1 ${SRC_LIST})
target_link_libraries(acado_test1 ${ACADO_SHARED_LIBRARIES})





