#include "pinocchio/parsers/sample-models.hpp"
#include "pinocchio/spatial/explog.hpp"
#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/algorithm/jacobian.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/parsers/urdf.hpp"
#include <iostream>

int main(int /* argc */, char ** /* argv */)
{
    //读取urdf模型
    const std::string urdf_filename = std::string("/home/d/githubPro/casadi_test/src/pinocco_test/pin_teach/arm.urdf");
  
    //加载模型
    pinocchio::Model model;
    pinocchio::urdf::buildModel(urdf_filename, model);
    pinocchio::Data data(model);
    //配置迭代参数
    const int JOINT_ID = 7;
    Eigen::VectorXd q = pinocchio::neutral(model);
    const double eps = 1e-4;
    const int IT_MAX = 1000;
    const double DT = 1e-1;
    const double damp = 1e-6;
    //设定雅可比矩阵
    pinocchio::Data::Matrix6x J(6,model.nv);
    Eigen::VectorXd v(model.nv);
    bool success = false;
    //设置目标位姿
    std::vector<pinocchio::SE3> targets {pinocchio::SE3(Eigen::Quaterniond(1, 0.0,0.0 ,0.0), Eigen::Vector3d(0.48,0.0 , 0.12)),};
    //开始利用雅可比矩阵迭代
    for (int idx = 0; idx < targets.size(); ++idx)
    {
        for (int i = 0;; i++)
        {
            //正运动学更新
            pinocchio::forwardKinematics(model, data, q);
            //获取误差矩阵
            const pinocchio::SE3 iMd = data.oMi[JOINT_ID].actInv(targets[idx]);
            std::cout<<"误差矩阵的大小为"<<iMd<<std::endl;
            //将误差矩阵转化为误差
            Eigen::Matrix<double, 6, 1> err = pinocchio::log6(iMd).toVector();  // in joint frame
            // std::cout<<<<std::endl;
            std::cout<<"err的大小为"<<err<<std::endl;
            if (err.norm() < eps)
            {
                success = true;
                break;
            }
            if (i >= IT_MAX)
            {
                success = false;
                break;
            }
            //获取雅可比矩阵
            pinocchio::computeJointJacobian(model, data, q, JOINT_ID, J);
            std::cout<<"J的大小为"<<J<<std::endl;
            pinocchio::Data::Matrix6 Jlog;
            //对雅可比矩阵的值进行修正
            pinocchio::Jlog6(iMd.inverse(), Jlog);
            J = -Jlog * J;
            std::cout<<"Jlog的大小为"<<Jlog<<std::endl;
            pinocchio::Data::Matrix6 JJt;
            JJt.noalias() = J * J.transpose();
            JJt.diagonal().array() += damp;
            std::cout<<"JJT的大小为"<<JJt<<std::endl;
            //获取关节角度微分
            v.noalias() = -J.transpose() * JJt.ldlt().solve(err);
            std::cout<<"v的大小为"<<v<<std::endl;
            //更新关节角度值
            q = pinocchio::integrate(model, q, v * DT);
            std::cout<<"q的大小为"<<q<<std::endl;
        }
        //输出结果
        std::cout << "Convergence achieved for configuration " << idx + 1 << std::endl;
        std::cout << "\nResult for configuration " << idx + 1 << ": " << q.transpose() << std::endl;
    }
}
