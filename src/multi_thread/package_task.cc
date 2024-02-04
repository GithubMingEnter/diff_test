
#include <future>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <algorithm>

#include <bits/stdc++.h>
// https://www.bilibili.com/video/BV1WP4y1c7MF/?spm_id_from=trigger_reload&vd_source=58ba16257efc07a6e9b9e0976f2f5200

int task1(int a, int b)
{
    a*=2;
    int ret_a = a * a;
    int ret_b = b * 2;
    int ret = ret_a + ret_b;
    return ret;
}
int task2(int* a, int b)
{
    *a*=2;
    int ret_a = *a * *a;
    int ret_b = b * 2;
    int ret = ret_a + ret_b;
    return ret;
}
void test2(){
    int ta=9,tb=6;
    std::future<int> fu_async=std::async(task2,&ta,tb);//)
    ta=3;
    std::cout<< "ta = "<< ta<<std::endl;
}
int main()
{
    test2();
    std::future<int> fu = std::async(task1, 1, 2);

    std::cout << "return value is " << fu.get() << std::endl;
    /* if deferred is called , it cannot create new thread to finish task and
    delay call task1*/
    /* if async is called ,run task1 in new thread */
    std::future<int> fu_defered = std::async(std::launch::async | std::launch::deferred,
                                             task1, 1, 2);
    std::cout << "return value is " << fu_defered.get() << std::endl;

    /* package_task */
    std::packaged_task<int(int,int)> t(task1);// int return type (int,int) param
    t(1,2);
    std::cout<<"t.get_future().get() = " << t.get_future().get() << std::endl;//get return value
    
    //transform parameter
    std::packaged_task<int(int,int)> tb(std::bind(task1,1,2));// do not need tb(1,2)
    // 获取一个 std::future 对象，用于获取任务的结果  
    std::future<int> fut=tb.get_future();
    // 将任务传递给线程
    // detach()函数的作用是将线程转换为后台守护进程，使其在后台运行，直到其任务完成。
    // 这样可以避免主线程结束后自动结束子线程的问题，也可以避免资源泄漏的问题。
    std::thread t1(std::move(tb),1,2);//w
    t1.detach();
    std::cout << " fut.get() value is " <<  fut.get() << std::endl;
    // t1.join();
    return 0;
}
