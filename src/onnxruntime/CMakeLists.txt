cmake_minimum_required(VERSION 3.10)

project(onnxruntime_test)






SET(onnxruntime_DIR /usr/local/include/onnxruntime/onnxruntime)
find_package(onnxruntime REQUIRED)


add_executable(onnxruntime_test test.cc)
target_link_libraries(
  onnxruntime_test
  onnxruntime
)