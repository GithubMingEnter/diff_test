#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/filters/radius_outlier_removal.h>
#include<pcl/filters/conditional_removal.h>
#include"pcl_type.h"
typedef pcl::PointXYZRGB PointT;

int main(int argc, char **argv) {
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);

    // Fill in the cloud data
    cloud->width = 50;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].r=255;

    }

    std::cerr << "Cloud before filtering: " << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cerr << "    " << cloud->points[i].x << " "
                  << cloud->points[i].y << " "
                  << cloud->points[i].z << std::endl;

    // Create the filtering object
    //build the 
    pcl::PassThrough<pcl::PointXYZRGB> pass;
    pass.setInputCloud(cloud);          // 1. 设置输入源
    pass.setFilterFieldName("z");       // 2. 设置过滤域名
    pass.setFilterLimits(0.0, 1.0);     // 3. 设置过滤范围
//    pass.setFilterLimitsNegative(true); // 设置获取Limits之外的内容
    pass.filter(*cloud_filtered);       // 4. 执行过滤，并将结果输出到cloud_filtered

    std::cerr << "Cloud after filtering: " << std::endl;
    for (size_t i = 0; i < cloud_filtered->points.size(); ++i)
        std::cerr << "    " << cloud_filtered->points[i].x << " "
                  << cloud_filtered->points[i].y << " "
                  << cloud_filtered->points[i].z << std::endl;
    for(int i=0;i<cloud_filtered->points.size();i++)
    {
        cloud_filtered->points[i].g=255;
    }
    // pcl::visualization::CloudViewer viewer("Cloud Viewer");

    // //这里会一直阻塞直到点云被渲染
    // viewer.showCloud(cloud);
    // while (!viewer.wasStopped()) {
    // } 
    pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_out_red(cloud,255,0,0);
    pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_out_green(cloud,0,255,0);

    // 创建PCLVisualizer
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->addPointCloud<PointT>(cloud,cloud_out_green,"raw cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,2,"raw cloud");

    viewer->addPointCloud<PointT>(cloud_filtered,cloud_out_red,"filter cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,3,"filter cloud");
    
    // 设置背景色为灰色（非必须）
    viewer->setBackgroundColor (0.05, 0.05, 0.05, 0);

    // 添加一个0.5倍缩放的坐标系（非必须）
    viewer->addCoordinateSystem (0.5);
    while(!viewer->wasStopped()){
        viewer->spinOnce();//循环调用重绘函数
    }
    return (0);
}