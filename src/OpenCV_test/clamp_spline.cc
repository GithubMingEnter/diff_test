#include <opencv2/opencv.hpp>
#include <cmath>
// TODO CHECK
// 计算Clamped曲线上的点
cv::Point2f calculateClampedCurvePoint(float t, const std::vector<cv::Point2f>& control_points, float start_yaw, float end_yaw) {
    // 计算Bezier曲线的点
    float x = pow(1 - t, 3) * control_points[0].x +
              3 * pow(1 - t, 2) * t * control_points[1].x +
              3 * (1 - t) * pow(t, 2) * control_points[2].x +
              pow(t, 3) * control_points[3].x;

    float y = pow(1 - t, 3) * control_points[0].y +
              3 * pow(1 - t, 2) * t * control_points[1].y +
              3 * (1 - t) * pow(t, 2) * control_points[2].y +
              pow(t, 3) * control_points[3].y;

    // 调整起点和终点处的偏航角
    if (t == 0) {
        x += cos(start_yaw);  
        y += sin(start_yaw);
    } else if (t == 1) {
        x += cos(end_yaw);
        y += sin(end_yaw);
    }

    return cv::Point2f(x, y);
}

int main() {
    // 创建一张空白图像
    cv::Mat image(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));

    // 定义起点、终点和起点终点处的偏航角
    cv::Point2f start_point(50, 400);
    cv::Point2f end_point(450, 400);
    float start_yaw = 0.5; // 起点偏航角
    float end_yaw = -0.5;  // 终点偏航角

    // 定义控制点
    std::vector<cv::Point2f> control_points = {
        start_point,
        cv::Point2f(150, 100),
        cv::Point2f(250, 300),
        cv::Point2f(350, 100),
        end_point
    };

    // 绘制控制点
    for (const auto& point : control_points) {
        cv::circle(image, point, 5, cv::Scalar(0, 0, 0), -1);
    }

    // 绘制起点和终点处的偏航角
    cv::arrowedLine(image, start_point, start_point + cv::Point2f(cos(start_yaw), sin(start_yaw)) * 50, cv::Scalar(0, 0, 255), 2);
    cv::arrowedLine(image, end_point, end_point + cv::Point2f(cos(end_yaw), sin(end_yaw)) * 50, cv::Scalar(0, 0, 255), 2);

    // 绘制Clamped曲线
    cv::Mat curve_image = image.clone();
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        cv::Point2f point = calculateClampedCurvePoint(t, control_points, start_yaw, end_yaw);
        cv::circle(curve_image, point, 1, cv::Scalar(0, 0, 0), -1);
    }

    // 显示结果
    cv::imshow("Clamped Curve", curve_image);
    cv::waitKey(0);
    return 0;
}
