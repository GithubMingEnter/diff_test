#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include "spdlog/async.h"   //add new  head file
int main(int, char* [])
{
    try 
    {
        // Create async_log file logger (not rotated)
        auto my_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_log_logger", "logs/async_log.txt");
        my_logger->info("daimon robotics #{}",520);
        
        spdlog::drop_all();
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}