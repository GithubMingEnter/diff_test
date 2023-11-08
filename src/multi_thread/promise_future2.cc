#include<iostream>
#include<future>
#include<condition_variable>
// https://www.bilibili.com/video/BV1XR4y1V7Yx/?spm_id_from=333.999.0.0&vd_source=58ba16257efc07a6e9b9e0976f2f5200

/* 
由于主线程和子线程都使用了ret变量，所以需要进行加锁，避免资源竞争
但是不方便,可以通过 future 和 promise获取得到
 */
using namespace std;
mutex mt;
condition_variable cd;

void task1(int a,int b,std::promise<int>& ret)
{
    int ret_a=a*a;
    int ret_b=b*2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a+ret_b);
}
// notice & 右值
void wait_task(int a,std::future<int>& b,std::promise<int>& ret)
{
    int ret_a=a*a;
    int ret_b=b.get()+2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a+ret_b);
}

void wait_multi_task(int a,std::shared_future<int> b,std::promise<int>& ret)
{
    int ret_a=a*a;
    
    int ret_b=b.get()+2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a+ret_b);
}
int main(){

    int ret=0;
    
    std::promise<int> p;
    std::future<int> f=p.get_future();//connect f and p

    std::thread t(task1,1,2,std::ref(p));    
    std::cout<<"return value is "<<f.get()<<endl;
    // f.get(); //get操作只能进行一次
    t.join(); //crash 

    /* wait task */
    std::promise<int> p_in,p_ret;
    std::future<int> f_in=p_in.get_future(),f_ret=p_ret.get_future();
    std::thread t_wait(wait_task,1,std::ref(f_in),std::ref(p_ret));
    // do sth else
    p_in.set_value(2);
    std::cout<<"return value is "<<f_ret.get()<<endl;

    t_wait.join();

    // //多个任务
    // std::promise<int> mp_in,mp_ret;
    // std::future<int> mf_in=mp_in.get_future(),mf_ret=mp_ret.get_future();
    
    // std::shared_future<int> sf(mp_in.get_future()) ;//p_in.get_future();
    // std::thread t_wait1(wait_multi_task,1,sf,std::ref(mp_ret));
    // // std::thread t_wait2(wait_multi_task,1,ref(sf),std::ref(mp_ret));
    // // std::thread t_wait3(wait_multi_task,1,ref(sf),std::ref(mp_ret));
    // // do sth else
    // // ....
    // mp_in.set_value(2);

    // std::cout<<"return value is "<<mf_ret.get()<<endl;                                 

    // t_wait1.join();

    // t_wait2.join();
    // t_wait3.join();
    return 0;
}









