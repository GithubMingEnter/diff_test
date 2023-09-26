#include<iostream>

#include<bits/stdc++.h>
#include<boost/thread.hpp>
#include <glog/logging.h>

void output_mes(const std::string str)
{
    std::cout<<str<<std::endl;
}
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&& ... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
void thread1_func()
{
    google::InitGoogleLogging("xx");
    LOG(INFO)<<"this is thread1_func ";
    google::ShutdownGoogleLogging(); // 关闭
    // for(int i=0;i<3;i++)
    // std::cout<<"this is thread1_func ";
}


int main()
{
   auto test_ptr = make_unique<boost::thread>(&thread1_func);
   test_ptr->join();
/*     boost::thread test_ptr(thread1_func);
    test_ptr.join(); */
    return 1;
}

