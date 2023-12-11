cmake_minimum_required(VERSION 2.8.9)

project(protobuf_test)


set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
link_libraries(${Protobuf_LIBRARY_DIRS})

add_executable(fileTest file.cc Person.pb.cc Address.pb.cc)
target_link_libraries(fileTest
${Protobuf_LIBRARIES}
)














