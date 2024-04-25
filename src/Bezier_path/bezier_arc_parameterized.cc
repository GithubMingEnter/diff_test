#include <iostream>

#include "opencv2/opencv.hpp"

#include "include/bezier.hpp"
#include <chrono>

using namespace cv;
using namespace std;

int main(){
    Mat img(500,700,CV_8UC3,Scalar(0));
    auto ts=std::chrono::steady_clock::now();
    std::initializer_list<Eigen::Matrix<double,2,1>> points{Eigen::Vector2d(1.0,2.0),Eigen::Vector2d(400,100),Eigen::Vector2d(320,300)};
    Bezier<2,2> bezier{{100,200},{400,100},{320,300}};
    // std::vector<Eigen::Matrix<double,2,1>> points{Eigen::Vector2d(1.0,2.0),Eigen::Vector2d(400,100),Eigen::Vector2d(320,300)};
    // Bezier<2,2> bezier(points);
    
    Eigen::Vector2d prev_point{0,0};
    vector<cv::Point> vec;
    double t=0.0,step=0.1;
    while (t <= 1.0) {
        auto ps4 = bezier.atWithArcLengthParameterized(t, 0, 4);
        vec.emplace_back(int(ps4[0]), int(ps4[1]));
        t += step;
    }
    auto te=std::chrono::steady_clock::now();
    auto tsum=std::chrono::duration_cast<std::chrono::milliseconds>(te-ts);
    std::cout<<tsum.count()<<std::endl;
    // bezier path
    polylines(img,vec, false, {0,23,234},1,LINE_AA);
    // equal arc length point
    t = 0,step=0.25;
    while(t<=1.0)
    {
        auto ps4 = bezier.atWithArcLengthParameterized(t,0,5);
        circle(img,{int(ps4[0]),int(ps4[1])},4,{0,255,0});
        if(prev_point != Eigen::Vector2d::Zero()){
            line(img,{int(prev_point[0]),int(prev_point(1))},
                    {int(ps4[0]),int(ps4[1])},
                    {245,35,233},
                    1,
                    LINE_AA
                );
                
        }
        prev_point=ps4;
        t+=step;
    }
    for(auto&p : bezier.sampleWithArcLengthParameterized(0.1,false,5)){
        cv::circle(img,{int(p[0]),int(p[1])},2,{255,0,0},1);
    }
    cv::imshow("arc-length parameterized of bezier curve",img);
    cv::waitKey(0);
    return 0;
}


