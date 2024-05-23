#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/algorithm/kinematics.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    using namespace pinocchio;

    // 加载 URDF 文件并建立模型
    const std::string urdf_filename = std::string("/home/d/githubPro/casadi_test/src/pinocco_test/pin_teach/arm.urdf");
    // 建立Model类型的模型
    Model model;
    // 将URDF模型导入到Model中
    pinocchio::urdf::buildModel(urdf_filename, model);
    std::cout << "Model name: " << model.name << std::endl;

    // 初始化数据结构
    Data data(model);

    // 定义关节角度配置
    // 设置状态量，其中最后一个状态量是夹爪伸缩量
    Eigen::VectorXd q(7); 
    q << 0, 1.57, 0, 0,  0, 0, 0; 
    for (JointIndex idx = 1; idx < model.njoints; ++idx) { 
        std::cout << "Joint #" << idx << ": " << model.names[idx] << std::endl;
    }
    // 计算正运动学，计算的结果保存在data中
    forwardKinematics(model, data, q);

    // 获取最后一个关节的索引
    JointIndex end_effector_id = model.njoints - 1; 
    std::cout << "End Effector Pose:" <<end_effector_id<< std::endl;
    //oMi表示相对于世界坐标系的绝对关节位置，translation表示提取齐次矩阵的平移部分，transpose表示取转置
    std::cout << "Position: " << data.oMi[end_effector_id].translation().transpose() << std::endl;

    // 将旋转矩阵转换为四元数表示,rotation表示提取齐次矩阵的旋转部分
    Eigen::Quaterniond quaternion(data.oMi[end_effector_id].rotation());
    std::cout << "Rotation (Quaternion): " << quaternion.coeffs().transpose() << std::endl;

    return 0;
}
