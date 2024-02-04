#include <iostream>
#include <future>
#include <condition_variable>
// https://www.bilibili.com/video/BV1XR4y1V7Yx/?spm_id_from=333.999.0.0&vd_source=58ba16257efc07a6e9b9e0976f2f5200

/*
由于主线程和子线程都使用了ret变量，所以需要进行加锁，避免资源竞争
但是不方便,可以通过 future 和 promise获取得到
步骤1
根据值的类型 定义 promise
然后利用promise变量获取得到future变量
将promise变量作为引用参数通过std::ref()传递
    通过set_value设定promise变量对象成员的值
通过 future变量获取得到更新的变量值，注意只能一次
然后释放线程
 */
using namespace std;
mutex mt;
condition_variable cd;

void task1(int a, int b, std::promise<int> &ret)
{
    int ret_a = a * a;
    int ret_b = b * 2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a + ret_b);
}
// notice & 右值
void wait_task(int a, std::future<int> &b, std::promise<int> &ret)
{
    int ret_a = a * a;
    int ret_b = b.get() + 2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a + ret_b);
}

void wait_multi_task(int a, std::shared_future<int> b, std::promise<int> &ret)
{
    int ret_a = a * a;

    int ret_b = b.get() + 2;
    // ret=ret_a+ret_b;
    ret.set_value(ret_a + ret_b);
}
int main()
{

    int ret = 0;

    std::promise<int> p;
    std::future<int> f = p.get_future(); // connect f and p

    std::thread t(task1, 1, 2, std::ref(p));
    std::cout << "return value is " << f.get() << endl;
    // f.get(); //get操作只能进行一次
    t.join(); // crash

    /* wait task */
    std::promise<int> p_in, p_ret;
    std::future<int> f_in = p_in.get_future(), f_ret = p_ret.get_future();
    std::thread t_wait(wait_task, 1, std::ref(f_in), std::ref(p_ret));
    // do sth else
    p_in.set_value(2);
    std::cout << "return value is " << f_ret.get() << endl;

    t_wait.join();

    // //多个任务
    std::promise<int> mp_in, mp_ret, mp_ret2, mp_ret3;
    std::future<int> mf_in,
        mf_ret = mp_ret.get_future(),
        mf_ret3 = mp_ret3.get_future(),
        mf_ret2 = mp_ret2.get_future();

    std::shared_future<int> sf(mp_in.get_future()); // p_in.get_future();
    // 按值传递参数，每个线程都持有一个share_future对象,但传入需要不同的promise
    std::thread t_wait1(wait_multi_task, 1, sf, std::ref(mp_ret));
    std::thread t_wait2(wait_multi_task, 1, sf, std::ref(mp_ret2));
    std::thread t_wait3(wait_multi_task, 1, sf, std::ref(mp_ret3));
    // do something else
    // ....
    mp_in.set_value(2);
    std::cout << std::endl << "share_future test" << std::endl;
    std::cout << "return value is " << mf_ret.get() << std::endl;
    std::cout << "return 2 value is " << mf_ret2.get() << std::endl;
    std::cout << "return 3 value is " << mf_ret3.get() << std::endl;

    t_wait1.join();

    t_wait2.join();
    t_wait3.join();
    return 0;
}
