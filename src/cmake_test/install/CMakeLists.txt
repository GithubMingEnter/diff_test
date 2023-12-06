# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (install)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
# modify install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build)
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
 
# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
	   "Use provided math implementation" ON)

option(USE_MYMATH 
        "Use my math implementation" ON)

#whether add library 
if(USE_MYMATH)
 include_directories("${PROJECT_SOURCE_DIR}/math")
 add_subdirectory(math)
 set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)

endif(USE_MYMATH)

#find all source file in current directory
#save file name to DIR_SRCS variable 

aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" 
        DESTINATION include)


# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test (test_run ${PROJECT_NAME} 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage ${PROJECT_NAME})
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 测试 5 的平方
# add_test (test_5_2 ${PROJECT_NAME} 5 2)

# set_tests_properties (test_5_2
#  PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 测试 10 的 5 次方
# add_test (test_10_5 ${PROJECT_NAME} 10 5)

# set_tests_properties (test_10_5
#  PROPERTIES PASS_REGULAR_EXPRESSION "is 100000")

# 测试 2 的 10 次方
# add_test (test_2_10 ${PROJECT_NAME} 2 10)

# set_tests_properties (test_2_10
#  PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")

# 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} ${PROJECT_NAME} ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# 利用 do_test 宏，测试一系列数据
do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")
