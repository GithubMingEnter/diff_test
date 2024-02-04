#include <glog/logging.h>

int main(int argc, char *argv[])
{
    // Initialize Google’s logging library.
    // change
    FLAGS_log_dir="/home/d/githubPro/casadi_test/build/logs/";
    // 最大日志大小（MB）
    FLAGS_max_log_size = 100;
    // FLAGS_logtostderr = false;     //如果FLAGS_logtostderr设置为true，日志将输出到标准输出；如果设置为false，则日志将输出到指定的文件中
    FLAGS_alsologtostderr = true;  // 设置日志消息除了日志文件之外还可显示到屏幕上
    FLAGS_colorlogtostderr = true; // 彩色打印输出
    google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::GLOG_INFO, "/home/d/githubPro/casadi_test/build/logs.log");
    LOG(INFO) << "This is an information message gogo";
    LOG(WARNING) << "This is a warning message";
    LOG(ERROR) << "This is an error message";

    /* 条件日志 */
    int num_cookies = 11;
    int size = 123;
    
    int i = 0;
    // num_cookies > 10才输出
    LOG_IF(INFO, num_cookies > 10)<< "Got lots of cookies";
    while (++i < 30)
    {
       // google::COUNTER 记录该语句被执行次数，从1开始，在第一次运行输出日志之后，每隔 10 次再输出一次日志信息
        LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
        //每隔 10 次去判断条件是否满足，如果滞则输出日志；而不是当满足某条件的情况下，每隔 10 次输出一次日志信息
	    LOG_IF_EVERY_N(INFO, (size > 1024), 10) << "Got the " << google::COUNTER << "th big cookie";  

        // 当此语句执行的前 20 次都输出日志，然后不再输出
        LOG_FIRST_N(WARNING, 20) << "first  " << google::COUNTER << " ";
    }
    google::ShutdownGoogleLogging(); // 关闭
}
