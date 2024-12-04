# Set the project name
project (cc_test)

find_package(glog REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
include_directories()
link_directories()
add_definitions()


add_executable(floydlib Floyd/floydlib.cc)
target_link_libraries(floydlib  
glog::glog
${Boost_LIBRARIES} 
)

add_executable(lambda_test modernCC/lambda_test.cc)
add_executable(function_test modernCC/function_test.cc)

add_executable(share_test modernCC/share_test.cc)


