
#include<bits/stdc++.h>
#include <boost/thread.hpp>
#include "test_thread.h"
using namespace std;
void outClassThreadFunc(int k) {
    cout << "Hello, outClassThreadFunc!" <<k<<endl;
}    
class MyClass {
public:
    void threadFunc() {
        cout << "Hello, world!" << endl;
    }
    void threadFuncP(int par) {
        cout << "Hello, world!" << par<<endl;
    }

    void startThread() {
        boost::thread t(&MyClass::threadFunc, this); // 创建线程，并绑定对象及成员函数
        t.join();


/* 类内绑定参数 */
        std::unique_ptr<boost::thread> test_ptr=std::make_unique<boost::thread>
                                                (boost::bind(&MyClass::threadFuncP,this,3));
        test_ptr->join();

    }
    void startOut(){
        {
            /* 调用同文件类外函数，出作用域自动join */
            boost::thread t(boost::bind(&outClassThreadFunc,3));
        }
        
    }
    void startOutFile(){
        { /* 调用头文件类外函数，出作用域自动join */
            boost::thread t(boost::bind(&outFileThreadFunc,4));
        }
    }
};
    
int main() {
    MyClass obj;
    obj.startThread();
    obj.startOut();
    obj.startOutFile();

    return 0;
}
