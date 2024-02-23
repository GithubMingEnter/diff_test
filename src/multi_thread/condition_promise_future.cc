#include<future>
#include<condition_variable>
#include<iostream>
// https://www.bilibili.com/video/BV1XR4y1V7Yx/?spm_id_from=333.999.0.0&vd_source=58ba16257efc07a6e9b9e0976f2f5200

/* 
由于主线程和子线程都使用了ret变量，所以需要进行加锁，避免资源竞争
但是不方便
 */
using namespace std;
mutex mt;
condition_variable cd;

void task1(int a,int b,int& ret)
{
    int ret_a=a*a;
    int ret_b=b*2;
    std::unique_lock<mutex> lock(mt);
    ret=ret_a+ret_b;
    cd.notify_one();

}


int main(){

    int ret=0;
    std::thread t(task1, 1,2,std::ref(ret));
    //do sth else
    // get the return value
    unique_lock<mutex> lock(mt);
    cd.wait(lock);
    std::cout<<"return value is "<<ret;
    t.join();
    return 0;
}









