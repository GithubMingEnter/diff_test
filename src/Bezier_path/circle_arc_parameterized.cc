#include <iostream>

#include "opencv2/opencv.hpp"

#include "include/arc.hpp"
#include <chrono>

using namespace cv;
using namespace std;

int main(){
    Mat img(500,700,CV_8UC3,Scalar(0));
    auto ts=std::chrono::steady_clock::now();
    // std::initializer_list<Eigen::Matrix<double,2,1>> points{Eigen::Vector2d(1.0,2.0),Eigen::Vector2d(400,100),Eigen::Vector2d(320,300)};
    // Bezier<2,2> bezier{{100,200},{400,100},{320,300}};
    std::vector<Eigen::Matrix<double,2,1>> points{Eigen::Vector2d(350.0,150.0),
                                                  Eigen::Vector2d(250.0,250.0)};
    Eigen::Vector2d center = Eigen::Vector2d(350.0,250.);
    Arc<2,2> arc(points,center);                                           
    // Arc<2,2> arc=Arc<2,2>(points,center);
    vector<cv::Point> vec,vecCtrl;
    double t=0.,step=0.1;
    while(t<=1.0){
        //  auto ps4 = arc.at(t, 0);
        auto ps4=arc.atWithArcLengthParameterized(t,0,4);
        vec.emplace_back(int(ps4[0]), int(ps4[1]));
        t += step;
    }
    auto te=std::chrono::steady_clock::now();
    auto tsum=std::chrono::duration_cast<std::chrono::milliseconds>(te-ts);
    std::cout<<tsum.count()<<std::endl;
    std::cout<<arc.length()<<"<-length "<<std::endl;
    polylines(img,vec, false, {0,23,234},1,LINE_AA);
    for(int i=0;i<2;i++){
        vecCtrl.emplace_back(int(points[i](0)), int(points[i](1)));
        circle(img,{int(points[i](0)),int(points[i](1))},4,{0,255,0});
    }
    polylines(img,vecCtrl, false, {0,23,234},1,LINE_AA);
        t = 0,step=0.25;

    Eigen::Vector2d prev_point{0,0};    
    while(t<=1.0)
    {
        auto ps4 = arc.atWithArcLengthParameterized(t,0,5);
        // circle(img,{int(ps4[0]),int(ps4[1])},4,{0,255,0});
        if(prev_point != Eigen::Vector2d::Zero()){
            /* line(img,{int(prev_point[0]),int(prev_point(1))},
                    {int(ps4[0]),int(ps4[1])},
                    {245,35,233},
                    1,
                    LINE_AA
                ); */
                
        }
        prev_point=ps4;
        t+=step;
    }
    for(auto&p : arc.sampleWithArcLengthParameterized(15,true,5)){
        std::cout<<"p = "<<p<<std::endl;
        cv::circle(img,{int(p[0]),int(p[1])},2,{255,0,0},1);
    }
    vector<cv::Point> vec1;
    // vec1.emplace_back(int(look_point(0)),int(look_point(1)));
    // vec1.emplace_back(int(nearest_point_xy(0)),int(nearest_point_xy(1)));
    // polylines(img,vec1, false, {0,222,234},1,LINE_AA);
    cv::imshow("arc-length parameterized of circle curve",img);
    cv::waitKey(0);
    return 0;
}


