#include<iostream>
#include<vector>

#include <Eigen/Eigen>


using Vec2d = Eigen::Vector2d;
using Vec2ds = std::vector<Vec2d>;
using Vec2i = Eigen::Vector2i;
using Vec3d = Eigen::Vector3d;
using Vec3ds = std::vector<Eigen::Vector3d>;

using Vec4d = Eigen::Vector4d;
using Vec4ds = std::vector<Eigen::Vector4d>;

using VecXd=Eigen::VectorXd;

using Matxd=Eigen::MatrixXd;

using namespace std;

int main(int argc,char* argv[])
{
    cout<<Vec2d::Zero()<<endl;
    
    return 0;
}


