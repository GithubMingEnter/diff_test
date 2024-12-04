#include "pinocchio/algorithm/rnea.hpp"
#include "pinocchio/algorithm/crba.hpp"
#include "pinocchio/algorithm/aba.hpp"
#include "pinocchio/parsers/urdf.hpp"

int main(int argc, char ** argv)
{
  using namespace pinocchio;
  
  //note 加载URDF文件
  const std::string urdf_filename = std::string("/home/d/githubPro/casadi_test/src/pinocco_test/pin_teach/arm.urdf");
  
  //URDF文件转化为model对象
  Model model;
  pinocchio::urdf::buildModel(urdf_filename,model);
  std::cout << "model name: " << model.name << std::endl;
  //设定一个关节角
  Eigen::VectorXd q(7);
  q << 0, 1.57, 0, 0, 0, 0, 0;
  Data data(model);
  //定义质量矩阵, nv express vector dim6y
  Eigen::MatrixXd M(model.nv, model.nv);
  //the computational inertia matrix is stored in data
  crba(model,data,q);

  //set the angular velocity and angular acceleration of the joint
  //  to 0 to obtain the gravitational moment
  Eigen::VectorXd tau_gravity = rnea(model, data, q, 
                              Eigen::VectorXd::Zero(model.nv), Eigen::VectorXd::Zero(model.nv));
  std::cout << "Gravity torques:\n" << tau_gravity.transpose() << std::endl;

  //set random joint angular acceleration
  Eigen::VectorXd qdd = Eigen::VectorXd::Random(model.nv);  
  std::cout << "Expect qdd" << qdd.transpose()<<std::endl;
  //设定关节角速度为0，角加速度随机，计算每个关节的力矩
   //rnea(model,data,q,dq,ddq)
  Eigen::VectorXd tau = rnea(model, data, q, Eigen::VectorXd::Zero(model.nv), qdd);
  std::cout<<"tau="<<tau<<std::endl;
  //计算关节角加速度
  //aba(model,data,q,dq,tau)
  aba(model, data, q, Eigen::VectorXd::Zero(model.nv), tau);
  std::cout << "Forward dynamics result (joint accelerations):\n" << data.ddq.transpose() << std::endl;

}

