cmake_minimum_required(VERSION 3.10)

project(diffcpp_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
option(GLOG_ON "build glog test" on)


include_directories(

)
# find_package(OpenCV REQUIRED)
find_package(OsqpEigen)
find_package(Eigen3)
find_package(glog 0.4.0 REQUIRED)

include_directories(${GLOG_INCLUDE_DER})
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

add_executable(eigen_test src/eigen_test/eigen_test.cc)






add_executable(${PROJECT_NAME}_perf src/test_perf.cc )



add_executable(test_spdlog src/test_spdlog.cc )
target_link_libraries(test_spdlog pthread glog::glog)

add_executable(spdlog2file src/spdlog2file.cc )
target_link_libraries(spdlog2file pthread)


add_executable(ipopt_test src/ipopt_test.cc)
target_link_libraries(ipopt_test ipopt)



add_executable(test_global_variable src/test_global_variable/globalVariable.cpp
src/test_global_variable/Derive.cpp
src/test_global_variable/Derive2.cpp

) 
#osqp_eigen
add_executable(osqp_eigen_test src/osqp_eigen_test.cc)
target_link_libraries(osqp_eigen_test OsqpEigen::OsqpEigen)


find_package(ompl REQUIRED)
include_directories(${OMPL_INCLUDE_DIRS})
link_directories(${OMPL_LIBRARY_DIRS})
add_definitions(${OMPL_DEFINITIONS})
find_package(Boost COMPONENTS system REQUIRED)
add_executable(test_rrtstar src/ompl_test/rrtstar.cc)
target_link_libraries(test_rrtstar ${Boost_LIBRARIES} ${OMPL_LIBRARIES})


add_executable(rrt_obs src/ompl_test/rrt_obstacle.cc)
target_link_libraries(rrt_obs ${Boost_LIBRARIES} ${OMPL_LIBRARIES})



add_executable(cc_test src/cc_test.cc)
target_link_libraries(cc_test ${Boost_LIBRARIES} )

SET(onnxruntime_DIR /usr/local/include/onnxruntime/onnxruntime)
find_package(onnxruntime REQUIRED)

add_subdirectory(src/ompl_test)
add_subdirectory(src/B_test)
add_subdirectory(src/glog_test)
add_subdirectory(src/multi_thread)
add_subdirectory(src/acado_test)
add_subdirectory(src/nlopt_test)

# add_subdirectory(src/pcl_test)

# add_subdirectory(src/protobuf_test)
add_subdirectory(src/OpenCV_test)

add_subdirectory(src/cmake_test)
add_subdirectory(src/casadi_test)
add_subdirectory(src/Bezier_path)
add_subdirectory(src/pinocco_test)