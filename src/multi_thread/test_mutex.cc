#include <iostream>
#include <thread>
#include <mutex>

// 定义全局变量
int global_variable1 = 0;
int global_variable2 = 0;
std::mutex mtx; // 互斥锁，用于保护全局变量的访问

// 第一个线程，修改全局变量的值
void thread_function() {
    // 对全局变量进行操作前，先获取互斥锁
    mtx.lock();
    global_variable1 += 10;
    global_variable2 -= 5;
    std::cout << "Thread 1: Modified global_variable1 = " << global_variable1 << ", global_variable2 = " << global_variable2 << std::endl;
    // 操作完成后，释放互斥锁
    mtx.unlock();
}

int main() {
    // 创建第一个线程
    std::thread thread1(thread_function);

    // 主线程修改全局变量的值
    mtx.lock();
    global_variable1 += 5;
    global_variable2 -= 2;
    std::cout << "Main thread: Modified global_variable1 = " << global_variable1 << ", global_variable2 = " << global_variable2 << std::endl;
    mtx.unlock();

    // 等待第一个线程执行完毕
    thread1.join();

    return 0;
}