#include <iostream>
#include <thread>
#include <chrono>

// 定时任务函数，接受定时时间作为参数
void timerFunction(bool &stop, int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds)); // 等待指定的时间

    // 指定时间后将 stop 设为 true 以跳出循环
    stop = true;
}

int main()
{
    bool stop = false;
    int customTime = 5; // 自定义的定时时间（秒）

    // 创建一个线程执行定时任务，将自定义的时间传递给定时器函数
    std::thread timer(timerFunction, std::ref(stop), customTime);

    // 循环直到 stop 为 true
    while (!stop)
    {
        // 在此处执行需要重复的操作

        // 等待一小段时间（可选）
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 为了避免 CPU 占用过高，可以在每次循环中暂停一小段时间
    }
    if (stop)
    {
        std::cout << "finish task" << std::endl;
    }

    // 等待定时器线程结束
    if (timer.joinable())
    {
        timer.join();
    }

    std::cout << "Loop exited after " << customTime << " seconds!" << std::endl;

    /*
    lambda 
     */
    stop = false;
    auto stopTime=[&stop,customTime](){
        std::this_thread::sleep_for(std::chrono::seconds(customTime));
        stop=true;
    };
    std::thread timer2(stopTime,std::ref(stop),3);

    // 循环直到 stop 为 true
    while (!stop)
    {
        // 在此处执行需要重复的操作

        // 等待一小段时间（可选）
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 为了避免 CPU 占用过高，可以在每次循环中暂停一小段时间
    }
    if (stop)
    {
        std::cout << "finish task" << std::endl;
    }

    // 等待定时器线程结束
    if (timer2.joinable())
    {
        timer2.join();
    }

    return 0;
}
