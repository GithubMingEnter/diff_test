project(casadi_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})



file(GLOB SOURCE *.cc *.cpp)

foreach(SOURCE_FILE ${SOURCE})
    # extract file name without extendsion name
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${FILE_NAME}_casadi ${SOURCE_FILE})
    target_link_libraries(${FILE_NAME}_casadi casadi)
endforeach()

