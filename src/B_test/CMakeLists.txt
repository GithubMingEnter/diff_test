project(bspline)

find_package(Eigen3 REQUIRED)
find_package(NLopt REQUIRED)

include_directories(

${Eigen3_INCLUDE_DIRS}
${NLOPT_INCLUDE_DIRS}
)


add_executable(b1 B_spline1.cc)
target_link_libraries(b1 ${NLOPT_LIBRARIES})


