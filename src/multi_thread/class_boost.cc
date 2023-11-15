
#include <bits/stdc++.h>
#include <boost/thread.hpp>
#include "test_thread.h"

#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

using namespace std;
void outClassThreadFunc(int k)
{
    cout << "Hello, outClassThreadFunc!" << k << endl;
}
class MyClass
{
    int con_var;
    using write_read_mtx = boost::mutex;
    using write_lock = boost::unique_lock<write_read_mtx>;
    using read_lock = boost::shared_lock<write_read_mtx>;
    bool ready = false; // 共享变量
    mutable write_read_mtx wr_mtx,wr_mtx1;
    boost::condition_variable cv; //
public:
    bool init()
    {
        con_var = 0;
        boost::thread t2(&MyClass::use2,this);
        boost::thread t1(&MyClass::use1,this);
        
        boost::thread t4(&MyClass::use4,this);
        boost::thread t3(&MyClass::use3,this);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        return true;
    }
    void use1()
    {
        write_lock wLock(wr_mtx1);
        while (1)
        {
            {
                /* template<typename predicate_type>
                void wait(unique_lock<mutex>& m,predicate_type pred)
                {
                    while (!pred())
                    {
                        wait(m);
                    }
                } */
                cv.wait(wLock, [&]
                        { return ready == 0; });
                // 等待资源非空
                con_var++;
                std::cout << "use1 con = " << con_var << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                ready = true;
                // wLock.unlock();
                cv.notify_all();
            }
        }
    }
    void use2()
    {
        write_lock rLock(wr_mtx1);
        while (1)
        {
            {
                cv.wait(rLock, [&]
                        { return ready != 0; }); // 等待资源非空
                std::cout << "use2 con = " << con_var << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                ready = false;
                cv.notify_all();
            }
        }
    }
    void use3()
    {
        
        while (1)
        {
            write_lock wLock(wr_mtx);
            con_var++;
            // cv.notify_all();
            wLock.unlock();
            std::cout << "use3 con = " << con_var << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ready = true;
            
            
        }
    }
    /* 
    use4() only read con_var
    
     */
    void use4()
    {
        
        while (1)
        {
            write_lock rLock(wr_mtx);
            // cv.wait(rLock); 
            std::cout << "use4 con = " << con_var << std::endl;
            rLock.unlock();
            //because delay exists , so programme can switch thread
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ready = false;
        }
    }
    void threadFunc()
    {
        cout << "Hello, world!" << endl;
    }
    void threadFuncP(int par)
    {
        cout << "Hello, world!" << par << endl;
    }

    void startThread()
    {
        boost::thread t(&MyClass::threadFunc, this); // 创建线程，并绑定对象及成员函数
        t.join();

        /* 类内绑定参数 */
        std::unique_ptr<boost::thread> test_ptr = std::make_unique<boost::thread>(boost::bind(&MyClass::threadFuncP, this, 3));
        test_ptr->join();
    }
    void startOut()
    {
        {
            /* 调用同文件类外函数，出作用域自动join */
            boost::thread t(boost::bind(&outClassThreadFunc, 3));
        }
    }
    void startOutFile()
    {
        { /* 调用头文件类外函数，出作用域自动join */
            boost::thread t(boost::bind(&outFileThreadFunc, 4));
        }
    }
};

int main()
{
    MyClass obj;
    obj.init();
    // obj.startThread();
    // obj.startOut();
    // obj.startOutFile();

    return 0;
}
