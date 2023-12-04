# Set the project name
project (pcl_test)


find_package(PCL REQUIRED)

include_directories(
    include
    ${PCL_INCLUDE_DIRS})
link_libraries(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

message(STATUS "PCL include: ${PCL_DIR})")
message(STATUS "PCL PCL_LIBRARIES: ${PCL_LIBRARIES})")



add_executable(show 01view/show.cc)
target_link_libraries(show ${PCL_LIBRARIES})

add_executable(viewr 01view/viewr.cc)
target_link_libraries(viewr ${PCL_LIBRARIES})


add_executable(transform 02pcl_common/transform.cc)
target_link_libraries(transform ${PCL_LIBRARIES})

add_executable(io 03io/io.cc)
target_link_libraries(io ${PCL_LIBRARIES})

add_executable(octree 04topology/octree.cc)
target_link_libraries(octree ${PCL_LIBRARIES})

add_executable(kd_tree 04topology/kd_tree.cc)
target_link_libraries(kd_tree ${PCL_LIBRARIES})

add_executable(ransac 05sample/ransac.cc)
target_link_libraries(ransac ${PCL_LIBRARIES})

add_executable(plane_pcl_split 12segmentation/plane_pcl_split.cc)
target_link_libraries(plane_pcl_split ${PCL_LIBRARIES})




add_executable(plane_cube 12segmentation/plane_cube.cc)
target_link_libraries(plane_cube ${PCL_LIBRARIES})

add_executable(direct_pass 09filtering/direct_pass.cc)
target_link_libraries(direct_pass ${PCL_LIBRARIES})


add_executable(condition 09filtering/condition.cc)
target_link_libraries(condition ${PCL_LIBRARIES})

