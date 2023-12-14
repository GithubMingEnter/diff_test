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





