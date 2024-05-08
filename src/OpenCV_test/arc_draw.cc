#include <opencv2/opencv.hpp>  
#include <cmath>  
using namespace cv;
using namespace std;
int main() {  
    // 创建一个空白图像  
    cv::Mat img = cv::Mat::zeros(Size(500, 500), CV_8UC3);  
  
    // 定义圆心、半径和颜色  
    Point center(250, 250);  
    int radius = 100;  
    Scalar color(0, 255, 0); // 绿色  
    int thickness = 2;  
  
    // 已知起点和终点  
    Point start_point(100, 300);  
    Point end_point(400, 200);  
  
    // 计算起点和终点的角度  
    double angle_start = atan2(start_point.y - center.y, start_point.x - center.x) * 180.0 / CV_PI;  
    double angle_end = atan2(end_point.y - center.y, end_point.x - center.x) * 180.0 / CV_PI;  
  
    // 确保起始角度小于或等于结束角度  
    if (angle_end < angle_start) {  
        angle_end += 360;  
    }  
  
    // 绘制圆弧  
    int startAngle = static_cast<int>(std::round(angle_start));  
    int endAngle = static_cast<int>(std::round(angle_end));  
    cv::ellipse(img, center, Size(radius, radius), startAngle, endAngle, 180, color, thickness, LINE_AA, 0);  
    cv::ellipse(img, center, Size(radius, radius), 0, 0, 360, Scalar(22,33,11), thickness, LINE_AA, 0); 
    // 显示图像  
    cv::imshow("Arc", img);  
    cv::waitKey(0);  
    return 0;  
}

