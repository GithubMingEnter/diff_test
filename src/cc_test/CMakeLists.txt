# Set the project name
project (cc_test)

find_package(glog REQUIRED)
include_directories()
link_directories()
add_definitions()
find_package(Boost COMPONENTS system REQUIRED)

add_executable(floydlib Floyd/floydlib.cc)
target_link_libraries(floydlib  glog::glog)





