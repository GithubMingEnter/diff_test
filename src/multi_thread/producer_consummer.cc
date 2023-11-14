#include <iostream>  
#include <future>  
#include <thread>  
#include <functional>  
  
using namespace std;

template<typename T>
class SafeQueue
{
public:
    SafeQueue() = default;
    SafeQueue() = default;
    SafeQueue(const SafeQueue& other) = delete;
    SafeQueue( SafeQueue&& other)=delete;

    SafeQueue& operator=(const SafeQueue& other)=delete;
    SafeQueue& operator=(const SafeQueue&& other) = delete;

    bool empty(){
        std::unique_lock<mutex> lock(mt_);
        return que_.empty()
    }

    int size(){
        unique_lock<mutex> lock(mt_);
        return que_.size();
    }
    void push(T& value)
    {
        unique_lock<mutex> lock(mt_);
        que_.push(value);
    }

    void push(T&& value)
    {
        unique_lock<mutex> lock(mt_);
        que.push(value);
    }
    void pop(T& value)
    {
        unique_lock<mutex> lock(mt_);
        if(que_.empty()){
            return false;
        }
        else{
            value=std::move(que_.front());
            que_.pop();
            return true;
        }
    }



private:
    std::queue<T> que_;
    std::mutex mt_;
} ;





