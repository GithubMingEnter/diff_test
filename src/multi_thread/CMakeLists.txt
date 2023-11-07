# Set the project name
project (thread_test)
set(CMAKE_CXX_STANDARD 14)
find_package(glog REQUIRED)

find_package(Boost COMPONENTS system REQUIRED)

add_executable(boost_bind_test boost_bind_test.cc)
target_link_libraries(boost_bind_test pthread 
${Boost_LIBRARIES} 
${Boost_FILESYSTEM_LIBRARY}
${Boost_PROGRAM_OPTIONS_LIBRARY}
glog::glog
boost_thread #note
)



add_executable(class_boost class_boost.cc)
target_link_libraries(class_boost pthread 
${Boost_LIBRARIES} 
${Boost_FILESYSTEM_LIBRARY}
${Boost_PROGRAM_OPTIONS_LIBRARY}
glog::glog
boost_thread #note
)

add_executable(future future.cc)
target_link_libraries(future pthread 

)


add_executable(read_write read_write.cc)
target_link_libraries(read_write pthread 
${Boost_LIBRARIES} 
${Boost_FILESYSTEM_LIBRARY}
${Boost_PROGRAM_OPTIONS_LIBRARY}
glog::glog
boost_thread #note
)

# add_executable(priority priority.cc)
# target_link_libraries(priority pthread 
# ${Boost_LIBRARIES} 
# ${Boost_FILESYSTEM_LIBRARY}
# ${Boost_PROGRAM_OPTIONS_LIBRARY}
# glog::glog
# boost_thread #note
# )
add_executable(priority2 priority.cc)
target_link_libraries(priority2 pthread 
${Boost_LIBRARIES} 
${Boost_FILESYSTEM_LIBRARY}
${Boost_PROGRAM_OPTIONS_LIBRARY}
glog::glog
boost_thread #note
)