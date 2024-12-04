#include "pinocchio/parsers/sample-models.hpp"
#include "pinocchio/spatial/explog.hpp"
#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/algorithm/jacobian.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/parsers/urdf.hpp"
#include <iostream>

using namespace std;
using namespace pinocchio;
int main(int /* argc */, char ** /* argv */)
{
    //读取urdf模型
    const std::string urdf_filename = std::string("/home/d/githubPro/casadi_test/src/pinocco_test/pin_teach/arm.urdf");
  
    //加载模型
    pinocchio::Model model;
    pinocchio::urdf::buildModel(urdf_filename, model);
    pinocchio::Data data(model);
    const int JOINT_ID =7 ;
    Eigen::VectorXd q = pinocchio::neutral(model);
    const double eps=1e-4;
    const double DT = 1e-1; // Time step for integration
    const double damp = 1e-6;///Damping factor to enhance numerical stability.
    const int IT_MAX = 1000;
    // SET jacobain matrix
    Data::Matrix6x J(6,model.nv);
    Eigen::VectorXd v(model.nv);
    bool success = false;
    // set goal position 
    vector<SE3> target{SE3(Eigen::Quaterniond(1,0.0,0.0,0.0),
                        Eigen::Vector3d(0.48,0.0,0.12)),};
    cout<<"target size = "<<target.size()<<endl;
    // by using jacobian matrix 
    for(int idx = 0;idx <target.size();++idx){
        for(int i=0;;++i){
            //kinematics update
            forwardKinematics(model,data,q);
            // get error matrix
            // oMi is a vector of SE3 objects within the data structure.
            //  Each SE3 object represents the transformation from 
            //  the origin (or base) frame to the i-th joint frame.
            const SE3 iMd = data.oMi[JOINT_ID].actInv(target[idx]);
            cout<<"error matrix = "<<iMd<<endl;
            //transform error matrix to error vector，SE3 -> se(3) transform to twist
            Eigen::Matrix<double,6,1> err = pinocchio::log6(iMd).toVector();
            cout<<"error ="<<err<<endl;
            if(err.norm()<eps){
                success = true;
                break;
            }
            if(i>=IT_MAX)
            {
                success = false;
                break;
            }
            computeJointJacobian(model,data,q,JOINT_ID,J);
            cout<<"J = "<<J<<endl;
            Data::Matrix6 Jlog;
            // modify jacobian matrix value updated error matrix
            Jlog6(iMd.inverse(),Jlog);
            J=-Jlog*J;
            cout<<"Jlog = \n "<<Jlog<<endl;
            Data::Matrix6 JJt;
            JJt.noalias() = J*J.transpose();
            //  add diagonal damping factor to enhance the numerical stability-to prevent Jacobian strangeness
            JJt.diagonal().array()+=damp;
            cout<<"JJT = "<<JJt<<endl;
            // get joint diff, JJt.ldlt().solver(err) is actually inversing JJt
            v.noalias() = -J.transpose()*JJt.ldlt().solve(err);
            cout<<"v = "<<v<<endl;
            // update joint angle value
            q=pinocchio::integrate(model,q,v*DT);


        }
        std::cout << "Convergence achieved for configuration " << idx + 1 << std::endl;
        std::cout << "\nResult for configuration " << idx + 1 << ": " << q.transpose() << std::endl;
    }
    
    return 0;
}