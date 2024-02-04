// #include <iostream>
// using std::cout;
// using std::endl;
// #include <vector>
// using std::vector;
// #include <sstream>
// #include <string>
// using std::string;
// #include <algorithm>

// #include <thread>
// #include <future>

// int GetVectorMax(const vector<int>& vec) {
//     return *(std::max_element(vec.begin(), vec.end()));
// }

// void PrintIntValueOnShared(std::shared_future<int>& s_fu) {
//     s_fu.wait();
//     std::stringstream ss;
//     ss << std::this_thread::get_id() << " Value: " << s_fu.get();
//     cout << ss.str() << endl;
//     return;
// }

// int main()
// {
//     vector<int> vec = { 1, 2, 3, 4, 5 };

//     std::packaged_task<int(const vector<int>&)> pt(GetVectorMax);
//     std::shared_future<int> s_fu(pt.get_future());

//     std::thread t1(&PrintIntValueOnShared, ref(s_fu));
//     std::thread t2(&PrintIntValueOnShared, ref(s_fu));
//     std::thread t3(&PrintIntValueOnShared, ref(s_fu));

    

//     std::thread(ref(pt), ref(vec)).join();

//     t1.join();
//     t2.join();
//     t3.join();

//     return EXIT_SUCCESS;
// }

#include <iostream>  
#include <future>  
#include <thread>  
#include <functional>  
  
// 函数原型  
int calculate(int x) {  
    return x * 2;  
} 
double calculate_d(int x){
    return x*3.5;
}
void test_pk(){
    std::packaged_task<double(int)> task_d(std::bind(calculate_d,3));
    std::future<double> res=task_d.get_future();
    // std::thread th_d(std::move(task_d),3);
    std::thread th_d(std::move(task_d),3);
    std::cout << "Result is: " << res.get() << std::endl;  
    if(th_d.joinable())
    {
        th_d.join();
    }
}
// TODO 
//detach experiment

int main() {  
    
    // 使用 std::bind 绑定函数和参数，创建一个 std::packaged_task 对象  
    std::packaged_task<int(int)> task(std::bind(calculate, 5));  
  
    // 获取一个 std::future 对象，用于获取任务的结果  
    std::future<int> result = task.get_future();  
  
    // 将任务传递给线程  
    std::thread(std::move(task), 5).detach();  
  
    // 在主线程中打印结果  
    std::cout << "Result is: " << result.get() << std::endl;  
    test_pk();
    return 0;  
}




