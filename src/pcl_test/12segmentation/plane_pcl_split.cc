#include<iostream>
#include<pcl/ModelCoefficients.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/sample_consensus/method_types.h> //随机参数估计方法
#include<pcl/sample_consensus/model_types.h>   
#include<pcl/segmentation/sac_segmentation.h> //基于采样一致性分割的类
#include <pcl/filters/extract_indices.h>    //抽取点云
#include"pcl_type.h"

#include <pcl/visualization/pcl_visualizer.h> // 可视化

using namespace std;
int main(int argc,char** argv)
{
    pc3_ptr cloud(new pc3);
    
    cloud->width=15;
    cloud->height=10;
    cloud->points.resize(cloud->width*cloud->height);

    //
    for(size_t i=0 ;i<cloud->size();i++)
    {
        cloud->points[i].x=1024*rand()/(RAND_MAX+1.0f);
        cloud->points[i].y=1024*rand()/(RAND_MAX+1.0f);
        cloud->points[i].z=1.0;
        
    }
    // 设置几个局外点，即重新设置几个点的z值，使其偏离z为1的平面
    cloud->points[0].z = 2.0;
    cloud->points[3].z = -2.0;
    cloud->points[6].z = 4.0;
     std::cerr << "Point cloud data: " << cloud->points.size() << " points" << std::endl; //打印
    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cerr << "    " << cloud->points[i].x << " "
                  << cloud->points[i].y << " "
                  << cloud->points[i].z << std::endl;   
    //创建分割时所需要的模型系数对象，参数及存储内点的点索引集合对象inliers
    MC_ptr coefficients(new MC);
    PI_ptr inliers(new PI);
    //创建分割对象
    pcl::SACSegmentation<p3> seg;
    //设置模型系数 ,可选择配置
    seg.setOptimizeCoefficients(true);
    //设置分割模型类型，所用的随机参数估计方法，距离阈值，输入点云
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);//设置随机采样一致性方法类型
    seg.setDistanceThreshold(0.01); //设定距离阈值,决定点被认为是局内点的条件

    seg.setInputCloud(cloud);
    //引发分割实现，存储分割结果到点几何inliers及存储平面模型的系数coefficients
    seg.segment(*inliers,*coefficients);
    //打印出平面模型
    std::cerr << "Model coefficients: " << coefficients->values[0] << " "
              << coefficients->values[1] << " "
              << coefficients->values[2] << " "
              << coefficients->values[3] << std::endl;

    std::cerr << "Model inliers: " << inliers->indices.size() << std::endl;
    for (size_t i = 0; i < inliers->indices.size(); ++i)
        std::cerr << inliers->indices[i] << "    " << cloud->points[inliers->indices[i]].x << " "
                  << cloud->points[inliers->indices[i]].y << " "
                  << cloud->points[inliers->indices[i]].z << std::endl;   
    //从点云中抽取分割的处在在平面上的点集
    pcl::PCDWriter writer;                                    //PCD文件读取对象
    pcl::ExtractIndices<p3> extract;                      //点提取对象
    pc3_ptr cloud_plane(new pc3());
    extract.setInputCloud(cloud);
    extract.setIndices(inliers);
    extract.setNegative(false);//设置是否应适用点过滤的常规条件，还是反的条件。
    extract.filter(*cloud_plane);
    std::cerr << "PointCloud representing the planar component: " << cloud_plane->points.size() << " data points." << std::endl;
    writer.write("plane.pcd",*cloud_plane,false);

     // 可视化
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("three windows "));
    int v1(0); //设置左右窗口
    int v2(1);
    viewer->createViewPort(0.0,0.0,0.9,0.5,v1);//(Xmin,Ymin,Xmax,Ymax)设置窗口坐标
    viewer->createViewPort(0.0,0.0,1.0,0.5,v2);
    pcl::visualization::PointCloudColorHandlerCustom<p3> cloud_out_red(cloud,255,0,0);
    viewer->addPointCloud(cloud,cloud_out_red,"raw pointcloud",v1);

     pcl::visualization::PointCloudColorHandlerCustom<p3> cloud_out_green(cloud,0,255,0);
    viewer->addPointCloud(cloud_plane,cloud_out_green,"raw pointcloud2",v2);
    viewer->spin();
    // 2. 非阻塞式
    // while (!viewer->wasStopped())
    // {
    //     viewer->spinOnce();
    // }
    return 0;
}
