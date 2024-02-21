# Set the project name
project (thread_test)
set(CMAKE_CXX_STANDARD 17)
find_package(glog REQUIRED)

find_package(Boost COMPONENTS system REQUIRED)

add_executable(test_band test_band.cc)
target_link_libraries(test_band pthread 

)



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
add_executable(promise_future promise_future.cc)
target_link_libraries(promise_future pthread 

)

add_executable(promise_future2 promise_future2.cc)
target_link_libraries(promise_future2 pthread 

)
add_executable(package_task package_task.cc)
target_link_libraries(package_task pthread 

)
add_executable(producer_consummer tasks/producer_consummer.cc)
target_link_libraries(producer_consummer pthread 

)

add_executable(thread_pool tasks/thread_pool.cc)
target_link_libraries(thread_pool pthread 

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



add_executable(test_mutex test_mutex.cc)
target_link_libraries(test_mutex pthread 

)
