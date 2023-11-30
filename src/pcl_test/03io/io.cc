#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int
main(int argc, char **argv) {
    // 准备pcl::PointXYZ类型的点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // 将pcd中的数据加载到cloud中
    if(pcl::io::loadPCDFile<pcl::PointXYZ>("./data/bunny.pcd",*cloud)==-1){
        PCL_ERROR("CANNOT LOAD POINTCLOUD");
        return -1;
    }
    std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from test_pcd.pcd with the following fields: "
              << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cout << "    " << cloud->points[i].x
                  << " " << cloud->points[i].y
                  << " " << cloud->points[i].z << std::endl;
    //serialization 
    pcl::io::savePCDFileASCII("ASCIIpcd.pcd",*cloud);
    // binary form
    pcl::io::savePCDFileBinary("test_pcd_binary.pcd", *cloud);

    return (0);
}