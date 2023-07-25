#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include "spdlog/sinks/daily_file_sink.h"

int main(int, char* [])
{
    try 
    {
        // 带日期信息，23:59轮换
        std::shared_ptr<spdlog::logger> my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
        my_logger->info("xxxxxxx");

        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("log_logger", 23,59);
        auto a_logger=std::make_shared<spdlog::logger>("a",daily_sink);
        auto b_logger=std::make_shared<spdlog::logger>("b",daily_sink);
        auto c_logger=std::make_shared<spdlog::logger>("c",daily_sink);

        a_logger->set_level(spdlog::level::critical);
        b_logger->set_level(spdlog::level::debug);
        c_logger->set_level(spdlog::level::err);


        //全局注册以便以便logger能够使用 spdlog::get(logger_name)访问到
        spdlog::register_logger(a_logger);
        // a_logger->error("daimon cr");  不会输出到文件中
        a_logger->critical("daimon cr");
        spdlog::register_logger(b_logger);
        b_logger->info("daimon deb");
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}




