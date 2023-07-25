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

add_executable(${PROJECT_NAME}_node src/casadi_test.cpp )
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} casadi) 

add_executable(${PROJECT_NAME}_node2 src/casadi_test2.cpp )
target_link_libraries(${PROJECT_NAME}_node2 ${catkin_LIBRARIES} casadi) 

add_executable(${PROJECT_NAME}_nodec src/casadi_test.cc )
target_link_libraries(${PROJECT_NAME}_nodec ${catkin_LIBRARIES} casadi) 



add_executable(${PROJECT_NAME}_perf src/test_perf.cc )



add_executable(test_spdlog src/test_spdlog.cc )
target_link_libraries(test_spdlog pthread)

add_executable(ipopt_test src/ipopt_test.cc)
target_link_libraries(ipopt_test ipopt)



add_executable(test_global_variable src/test_global_variable/globalVariable.cpp
src/test_global_variable/Derive.cpp
src/test_global_variable/Derive2.cpp

)   