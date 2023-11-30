#include<iostream>
#include<pcl/ModelCoefficients.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/sample_consensus/method_types.h> //随机参数估计方法
#include<pcl/sample_consensus/model_types.h>   
#include<pcl/segmentation/sac_segmentation.h> //基于采样一致性分割的类

using p3=pcl::PointXYZ;
using pc3=pcl::PointCloud<p3>;
using pc3_ptr=pc3::Ptr;


using MC=pcl::ModelCoefficients;
using MC_ptr=pcl::ModelCoefficients::Ptr;

using PI=pcl::PointIndices;
using PI_ptr=PI::Ptr;
