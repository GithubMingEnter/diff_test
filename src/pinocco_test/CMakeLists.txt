project(pinocchio_test)


find_package(pinocchio REQUIRED)

INCLUDE_DIRECTORIES(${PINOCCHIO_INCLUDE_DIRS})

add_executable(kinetic_node pin_teach/kinetic.cpp)
target_link_libraries(kinetic_node ${PINOCCHIO_LIBRARIES})

set(SOURCE_DIR "pin_teach")
# get source file list 
file(GLOB SOURCE ${SOURCE_DIR}/*.cc )
foreach(SOURCE_FILE ${SOURCE})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SOURCE_FILE})
    target_link_libraries(${FILE_NAME} ${PINOCCHIO_LIBRARIES})
endforeach()








