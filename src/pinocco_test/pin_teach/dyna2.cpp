#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/algorithm/frames.hpp"
#include "pinocchio/algorithm/rnea.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    using namespace pinocchio;

    const std::string urdf_filename = std::string("/home/zha/1_workspace/ros_test_ws/src/tank/urdf/only_arm_forp.urdf");

    Model model;
    pinocchio::urdf::buildModel(urdf_filename, model);
    std::cout << "model name: " << model.name << std::endl;

    Data data(model);

    Eigen::VectorXd q1(7);
    Eigen::VectorXd q2(7);
    Eigen::VectorXd q3(7);
    Eigen::VectorXd q4(7);
    q1 << -37.48, 36.69, 0, 90, 0, -64.57, -32.69;
    q2 << -8.32, 31.05, 3.10, 66.15, 0, -64.57, -32.69;
    q3 << -20, 31.05, 3.10, 66/15, 0, 0.36, -32.69;
    // q4 << 0, 1.57, 0, 1.57, 0, -1.57, 0;
    // Array of joint angles
    q1 = q1 / 180 * 3.1415; q3 = q3 / 180 * 3.1415; q2 = q2 / 180 * 3.1415;
    Eigen::VectorXd jointAngles[3] = {q1, q2, q3};

    // Interpolation and collecting data
    std::vector<Eigen::VectorXd> jointAngless;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            double alpha = static_cast<double>(j) / 50.0;
            Eigen::VectorXd q_interp = (1 - alpha) * jointAngles[i] + alpha * jointAngles[i + 1];
            jointAngless.push_back(q_interp);
        }
    }

    // Calculate joint torques and write to txt
    std::ofstream outFile("joint_torques.txt");
    for (size_t i = 0; i < jointAngless.size(); ++i)
    {
        Eigen::VectorXd &q = jointAngless[i];
        std::cout << "For joint configuration q" << i + 1 << ":" << std::endl;
        std::cout << "q: " << q.transpose() << std::endl;

        forwardKinematics(model, data, q);
        Eigen::VectorXd tau = rnea(model, data, q, Eigen::VectorXd::Zero(model.nv), Eigen::VectorXd::Zero(model.nv)); // Joint torques
        std::cout << "Joint torques: " << tau.transpose() << std::endl;
        
        // Write torques to txt file
        for (int j = 0; j < tau.size(); ++j) {
            outFile << tau[j] << " ";
        }
        outFile << std::endl;
    }
    outFile.close();

    return 0;
}
