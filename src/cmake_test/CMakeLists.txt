cmake_minimum_required(VERSION 3.10)

project(cmake_test)

#point source file directory
set(SOURCE_DIR "set")
# get source file list 
file(GLOB SOURCE ${SOURCE_DIR}/*.cc )

foreach(SOURCE_FILE ${SOURCE})
    # extract file name without extendsion name
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SOURCE_FILE})

endforeach()

# add_executable(listNode set/listNode.cc)

