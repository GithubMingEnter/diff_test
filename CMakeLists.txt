cmake_minimum_required(VERSION 2.8.9)

project(casadi_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(OpenCV REQUIRED)

# set(AS_SOURCES
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/AStar.cpp
# )

# set(AS_HEADERS
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/AStar.h
# )

include_directories(
  # include
  ${catkin_INCLUDE_DIRS}
)

# include_directories(include 
#                     maps
#                     "/home/seivl/my_lib/OOQP/include"
# )

# link_directories("/home/seivl/my_lib/OOQP/lib")

# add_executable(main src/main.cpp ${AS_HEADERS} ${AS_SOURCES})

# target_link_libraries(main 
#                     ${OpenCV_LIBS}
#                     ooqpgensparse
#                     ooqpsparse
#                     ooqpgondzio
#                     ooqpbase 
#                     blas 
#                     ma27 
#                     gfortran
# )
find_package(OsqpEigen)
find_package(Eigen3)
find_package(glog 0.4.0 REQUIRED)

include_directories(${GLOG_INCLUDE_DER})
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

add_executable(eigen_test src/eigen_test/eigen_test.cc)


add_executable(${PROJECT_NAME}_node src/casadi_test.cpp )
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} casadi) 

add_executable(${PROJECT_NAME}_node2 src/casadi_test2.cpp )
target_link_libraries(${PROJECT_NAME}_node2 ${catkin_LIBRARIES} casadi) 

add_executable(${PROJECT_NAME}_nodec src/casadi_test.cc )
target_link_libraries(${PROJECT_NAME}_nodec ${catkin_LIBRARIES} casadi) 



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


add_subdirectory(src/ompl_test)
add_subdirectory(src/B_test)
add_subdirectory(src/glog_test)
add_subdirectory(src/multi_thread)




