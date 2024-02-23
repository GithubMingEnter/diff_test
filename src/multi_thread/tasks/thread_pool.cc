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
} ;

// single task queue 
// commit task : 

 /* common function ,anonymous function ,functor func,
  overload operator (), class member func, std::function/std::packaged_task
  consider different return value and parameter lists  
   */
class SimpleThreadPool
{
public:
    SimpleThreadPool(const SimpleThreadPool&) = delete;
    SimpleThreadPool(const SimpleThreadPool&&) = delete;
    SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;
    SimpleThreadPool& operator=(const SimpleThreadPool&&)=delete; // move constructor

    SimpleThreadPool():thread_(std::thread::hardware_concurrency()),runningStatus_(true)
    {
        initialize();
    }
    SimpleThreadPool(int thread_num): thread_(thread_num),runningStatus_(true)
    {        
        initialize();
    }
    ~SimpleThreadPool(){
        runningStatus_=false;
        cv_.notify_all();
        for(auto& th:thread_){ //note &
            if(th.joinable()){
                th.join();
            }
        }
    }
    template<typename Func,typename ... Args>
    auto submitTask(Func&& func,Args ... args)
    {
        // wrap return value; c++17
        using returnType =typename std::invoke_result<Func,Args ...>::type;
       
            //erase parameter list
        std::function<returnType()> taskWrapper1 =std::bind(std::forward<Func>(func),std::forward<Args>(args)...);
                  //pre handle return value  package_task
        auto taskWrapper2 = std::make_shared<std::packaged_task<returnType()>> (taskWrapper1);
            //
        //get return value
        taskType wrapper_func = [taskWrapper2](){
            (*taskWrapper2)();
        };
        //put task queue
        task_que_.push(wrapper_func);
        //notify
        cv_.notify_one();
        //return value
        return taskWrapper2->get_future();
        //
    }
private:
    using taskType=std::function<void()> ;
    SafeQueue<taskType> task_que_;
    std::vector<std::thread> thread_;
    std::condition_variable cv_;
    std::atomic<bool> runningStatus_;//control running state
    std::mutex mtx_;

    void initialize()
    {
        for(int i=0;i<thread_.size();i++){
            auto worker=[this,i](){
                while(runningStatus_)
                {
                    taskType task;
                    bool isSuccess=false;
                    {
                        std::unique_lock<std::mutex> lock(mtx_);
                        if(this->task_que_.empty()){
                            this->cv_.wait(lock);

                        }
                        isSuccess=this->task_que_.pop(task);
                    } 
                    if(isSuccess){
                        std::cout<<"start running task in worker:[ID]"<<i<<"\n";
                        task();
                        std::cout<<"end running task in worker :[ID]"<<i<<"\n";
                    }                   
                }
            };
            thread_[i]=std::thread(worker);
        }
    }
};

int very_time(int a,int b){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return a+b;
}

int main(){
    SimpleThreadPool simple_thread_pool(12);
    int taskNum = 30;
    std::vector<std::future<int>> res(taskNum);
    std::cout << "start submit "<<std::endl;

    for(size_t i=0;i<taskNum;i++){
        simple_thread_pool.submitTask(very_time,i,i+1);
    }
    std::cout << "end submit "<<std::endl;
    // do sth else
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for(int i=0;i<res.size();i++){
        std::cout<<"result ["<<i<<"]="<<res[i].get()<<std::endl;//note get()
    }

    return 0;
}