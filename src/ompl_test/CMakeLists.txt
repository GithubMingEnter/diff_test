# Set the project name
project (ompl_test)

find_package(ompl REQUIRED)
include_directories(${OMPL_INCLUDE_DIRS})
link_directories(${OMPL_LIBRARY_DIRS})
add_definitions(${OMPL_DEFINITIONS})
find_package(Boost COMPONENTS system REQUIRED)

message(WARNING "${OMPL_INCLUDE_DIRS}")

add_executable(dubin kinomaticCarPath.cc)
target_link_libraries(dubin ${Boost_LIBRARIES} 
${OMPL_LIBRARIES}
${Boost_FILESYSTEM_LIBRARY}
${Boost_PROGRAM_OPTIONS_LIBRARY}
)





