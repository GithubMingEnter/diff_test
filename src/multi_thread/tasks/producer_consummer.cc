#include <iostream>  
#include <future>  
#include <thread>  
#include <functional>  
#include<vector>
#include<queue>

using namespace std;

template<typename T>
class SafeQueue
{
public:
    SafeQueue() = default;
   ~SafeQueue() = default;
    SafeQueue(const SafeQueue& other) = delete;
    SafeQueue( SafeQueue&& other)=delete;

    SafeQueue& operator=(const SafeQueue& other)=delete;
    SafeQueue& operator=(const SafeQueue&& other) = delete;

    bool empty(){
        std::unique_lock<mutex> lock(mt_);
        return que_.empty();
    }

    int size(){
        unique_lock<mutex> lock(mt_);
        return que_.size();
    }
    void push(T& value)
    {
        unique_lock<mutex> lock(mt_);
        que_.push(value);
        std::cout<<" thread id : "<<this_thread::get_id() <<std::endl;
    }

    void push(T&& value)
    {
        unique_lock<mutex> lock(mt_);
        que_.push(value);
    }
    bool pop(T& value)
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
    int maxSize_;
} ;

/* 
1.队列已满，不需要生产，只能消费, 生产者wait 条件变量
2.队列为空，只能生产，不能消费， 消费者wait条件变量
3.队列不满，既可以生产，也可以消费
 */


template<typename T>
class ProducerConsumer{
public:
    
    ProducerConsumer():producer_thread(20),consumer_thread(10),que_maxSize(30),RunningStatus_(true)
    {

    }
    ProducerConsumer(int que_size,int pro_t,int con_t):
        producer_thread(pro_t),consumer_thread(con_t),que_maxSize(que_size),RunningStatus_(true)
    {

    }
    ~ProducerConsumer()
    {
        RunningStatus_=false;
        que_NotEmptyCV.notify_all();
        que_NotFullCV.notify_all();
        for(size_t i=0;i<producer_thread.size();i++){
            if(producer_thread[i].joinable())
            {
                producer_thread[i].join();
            }
        }
        for(size_t i=0;i<consumer_thread.size();i++){
            if(consumer_thread[i].joinable())
            {
                consumer_thread[i].join();
            }
        }
    }
    void initialize(){
        for(size_t i=0;i<producer_thread.size();i++){
            producer_thread[i]=thread(&ProducerConsumer::producer,this);
        }
        for(size_t i=0;i<consumer_thread.size();i++){
            consumer_thread[i]=thread(&ProducerConsumer::consumer,this);
        }
    }
private:
    SafeQueue<T> que_;
    vector<thread> producer_thread,consumer_thread;
    atomic<bool> RunningStatus_;
    mutex mt_;
    condition_variable que_NotFullCV,que_NotEmptyCV;
    int que_maxSize;
    
    bool isFull()
    {
        if(que_.size()>=que_maxSize)
        {
            return true;
        }
        return false;
    }
    void producer(){
        while(RunningStatus_)
        {
            unique_lock<std::mutex> lock(mt_);
            if(isFull()){
                std::cout<<"queue is full ! waiting for queueNotFullCV\n";
                que_NotFullCV.wait(lock);

            }
            if(!isFull())
            {
                std::cout<<"queue is not full ! \n";
                T value =3 ;
                que_.push(value);
                que_NotEmptyCV.notify_one();//
            }
        }
        
    }
    void consumer(){
        while(RunningStatus_)
        {
            unique_lock<std::mutex> lock(mt_);
            if(que_.empty()){
                std::cout<<"queue is empty ! waiting for queueNotEmptyCV\n";
                que_NotEmptyCV.wait(lock);
            }
            if(!que_.empty())
            {
                std::cout<<"queue is not empty ! \n";
                T value  ;
                bool res=que_.pop(value);
                value++;
                std::cout<<"result = "<<value<<endl;
                que_NotFullCV.notify_one();//
            }
        }
    }
};

int main()
{
    ProducerConsumer<int> producer_consumer(100,30,40);
    producer_consumer.initialize();

    return 0;
}