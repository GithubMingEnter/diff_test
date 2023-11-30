#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/filters/radius_outlier_removal.h>
#include<pcl/filters/conditional_removal.h>

typedef pcl::PointXYZRGB PointT;

int main(int argc, char **argv) {
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);

    // Fill in the cloud data
    cloud->width = 50;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = 1024 * rand() / (RAND_MAX + 10.f)*10;
        cloud->points[i].y = 1024 * rand() / (RAND_MAX + 10.f)*10;
        cloud->points[i].z = 1024 * rand() / (RAND_MAX + 10.f);
        cloud->points[i].r=255;

    }

    std::cerr << "Cloud before filtering: " << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cerr << "    " << cloud->points[i].x << " "
                  << cloud->points[i].y << " "
                  << cloud->points[i].z << std::endl;

    // Create the filtering object
    //build the condition
    // 设置Y轴的限制范围 [-5.0, 5.0]
    pcl::ConditionAnd<PointT>::Ptr range_and(new pcl::ConditionAnd<PointT>());
    range_and->addComparison(pcl::FieldComparison<PointT>::ConstPtr (new
                pcl::FieldComparison<PointT>("y",pcl::ComparisonOps::GT,-5.0)));
    range_and->addComparison(pcl::FieldComparison<PointT>::ConstPtr (new
                pcl::FieldComparison<PointT>("y",pcl::ComparisonOps::LT,5.0)));     
     // 设置X轴的限制范围 [-5.0, 5.0]                
    range_and->addComparison(pcl::FieldComparison<PointT>::ConstPtr (new
                pcl::FieldComparison<PointT>("x",pcl::ComparisonOps::GT,-5.0)));
    range_and->addComparison(pcl::FieldComparison<PointT>::ConstPtr (new
                pcl::FieldComparison<PointT>("x",pcl::ComparisonOps::LT,5.0)));       
    pcl::ConditionalRemoval<PointT> condrem;
    condrem.setCondition(range_and);
    condrem.setInputCloud(cloud);                    

    // condrem.setKeepOrganized(true);
    //确认是否保存点云过滤后的结构信息如果设置为true的话，那么点不会移除，只是点的坐标全部变为NaN默认。
    // 所以在打印出过滤的点云个数竟然没有变化。设置为false时候，就是将这些点给滤除，不保留原始的点云结构。
  // apply filter
    condrem.filter(*cloud_filtered);

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