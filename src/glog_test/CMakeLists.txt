# Set the project name
project (glog_test)

find_package(glog REQUIRED)
include_directories(${OMPL_INCLUDE_DIRS})
link_directories(${OMPL_LIBRARY_DIRS})
add_definitions(${OMPL_DEFINITIONS})
find_package(Boost COMPONENTS system REQUIRED)

add_executable(test_glog test_glog.cc)
target_link_libraries(test_glog pthread glog::glog)





