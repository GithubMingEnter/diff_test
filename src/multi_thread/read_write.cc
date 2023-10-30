#include <iostream>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  
  
std::mutex mtx;          // 互斥锁  
std::condition_variable cv; // 条件变量  
  
int shared_resource = 0; // 共享资源  
  
void read_thread() {  
    std::unique_lock<std::mutex> lock(mtx);  
    while (true) {  
        cv.wait(lock, [] { return shared_resource != 0; }); // 等待资源非空  
        std::cout << "Read thread read data: " << shared_resource << std::endl; 
        std::this_thread::sleep_for(std::chrono::seconds(2));
        shared_resource=0;
 
        cv.notify_all(); // 通知其他线程可以访问资源  
    }  
}  
  
void write_thread() {  
    std::unique_lock<std::mutex> lock(mtx);  
    while (true) {  
        cv.wait(lock, [] { return shared_resource == 0; }); // 等待资源为空  
        shared_resource = 1; // 修改资源  
        std::cout << "Write thread read data: " << shared_resource << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        cv.notify_all(); // 通知其他线程可以访问资源  
    }  
}  
  
int main() {  
    std::thread t1(read_thread);  
    std::thread t2(write_thread);  
    t1.join();  
    t2.join();  
    return 0;  
}