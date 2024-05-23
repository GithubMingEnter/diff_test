#include<pinocchio/parsers/urdf.hpp>
#include<pinocchio/algorithm/joint-configuration.hpp>
#include<pinocchio/algorithm/kinematics.hpp>



#include<iostream>
using namespace std;
using namespace pinocchio;
int main(int argc,char **argv)
{
    const std::string urdf_filename = string("/home/d/githubPro/casadi_test/src/pinocco_test/pin_teach/arm.urdf");
    //build model
    Model model;

    //import urdf model to Model

    pinocchio::urdf::buildModel(urdf_filename,model);
    //init data structure
    Data data(model);
    // define joint angle
    
    //set state , while last state is Expansion and contraction of gripper
    Eigen::VectorXd q(7);
    q<< 0 ,1.57, 0, 0, 0, 0, 0;
    for(JointIndex i=1;i<model.njoints;++i){
     cout<<"Joint ."<<i<<": "<<model.names[i]<<endl;   

    }
    // calc kinematics ,save to data
    forwardKinematics(model,data,q);
    // last joint idx pos
    JointIndex end_jointIdx = model.njoints-1;
    cout<<"pos: "<<data.oMi[end_jointIdx].translation().transpose()<<endl;

    Eigen::Quaterniond quat(data.oMi[end_jointIdx].rotation());

    cout<<"rotation (quaternion)"<<quat.coeffs().transpose()<<endl;
    return 0;
}