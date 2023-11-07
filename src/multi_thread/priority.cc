#include <iostream>
#include <thread>
#include <pthread.h>
#include <sched.h>
void thread_func()
{
    while(1)
    {
        std::cout << "Thread " << 1 << " changed." << std::endl;
    }
      // 线程执行的任务
}
void thread_func2()
{
    while(1)
    {
        std::cout << "Thread " << 2 << " changed." << std::endl;
    }
      
}





int main()
{
    std::thread t(thread_func);
    std::thread t2(thread_func2);
    
    // 修改线程的调度策略和优先级
    int policy = SCHED_RR; // 设置为轮流调度
    int priority = 10; // 设置优先级为 10
    int priority2 = 20; // 设置优先级为 20
    pthread_attr_t attr;
    //初始化线程属性
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, policy);
    sched_param param,param2;
    // 设置优先级    
    param.sched_priority = priority;
    param2.sched_priority = priority2;

    // pthread_attr_setschedparam(&attr, &param);
    // pthread_attr_setschedparam(&attr, &param2);
    // // 设置线程继承调度属性
    // pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    // 转换为pthread线程
    pthread_t thread_handle = t.native_handle();
    pthread_t thread_handle2 = t2.native_handle();
    // 设置线程的调度策略和优先级
    pthread_setschedparam(thread_handle, policy, &param);
     pthread_setschedparam(thread_handle2, policy, &param2);
     //有时会设置失败
    // if(
        // pthread_setschedparam(thread_handle2, policy, &param2);
        // !=0)
    // {
    //     std::cerr << "Failed to set thread priority." << std::endl;  
    //     return -1;  
    // }

    t.join();
    t2.join();
    return 0;
}
