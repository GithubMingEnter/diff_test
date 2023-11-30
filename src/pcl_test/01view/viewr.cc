#include<pcl/visualization/pcl_visualizer.h>
#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h> //类cloud_viewer头文件申明

#include<iostream>

int user_data;
using Pv=pcl::visualization::PCLVisualizer ;
void viewerOneOff(pcl::visualization::PCLVisualizer &viewer)
{

    pcl::PointXYZ o;
    viewer.addSphere(o,0.5,"sphere");
    std::cout<<"draw circle"<<std::endl;
}


void viewerPsycho(Pv &viewer)
{
    static unsigned count=0;
    std::stringstream ss;
    ss<<"Once loop <<"<<count++;
    viewer.removeShape("text",0)
    ;
    viewer.addText(ss.str(),200,300,"text",0);
    user_data++;
}


int main(){
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;
    cloud.reset(new pcl::PointCloud<pcl::PointXYZRGBA>());
     pcl::visualization::CloudViewer viewer("visualize") ;
    viewer.showCloud(cloud);
    // 只会调用一次 (非必须)
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    // 每次可视化迭代都会调用一次（频繁调用） (非必须)
    viewer.runOnVisualizationThread (viewerPsycho);
    while (!viewer.wasStopped()) {
        user_data++;
    }
    return 0;
}

