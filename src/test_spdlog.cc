#include <glog/logging.h>

int main(int argc, char* argv[]) {
    // Initialize Google’s logging library.
    FLAGS_log_dir="/home/d/githubPro/casadi_test/build/logs/";
    FLAGS_alsologtostderr = true;  //设置日志消息除了日志文件之外还可显示到屏幕上

    google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::GLOG_INFO, "/home/d/githubPro/casadi_test/build/logs.log");
    LOG(INFO) << "This is an information message gogo";
    LOG(WARNING) << "This is a warning message";
    LOG(ERROR) << "This is an error message";
    google::ShutdownGoogleLogging();

}
