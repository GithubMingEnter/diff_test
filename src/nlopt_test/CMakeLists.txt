# Set the project name
# 终端直接编译 g++ nlopt_test1.cc -lnlopt -o nlopt_test
project (nlopt_test)

find_package(NLopt REQUIRED)  
include_directories(${NLopt_INCLUDE_DIRS})  
 
message( "${NLopt_INCLUDE_DIRS}")

add_executable(NloptExample nlopt_test1.cc)  
target_link_libraries(NloptExample ${NLOPT_LIBRARIES})



