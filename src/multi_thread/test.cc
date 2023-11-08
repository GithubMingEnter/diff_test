#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <sstream>
#include <string>
using std::string;
#include <algorithm>

#include <thread>
#include <future>

int GetVectorMax(const vector<int>& vec) {
    return *(std::max_element(vec.begin(), vec.end()));
}

void PrintIntValueOnShared(std::shared_future<int>& s_fu) {
    s_fu.wait();
    std::stringstream ss;
    ss << std::this_thread::get_id() << " Value: " << s_fu.get();
    cout << ss.str() << endl;
    return;
}

int main()
{
    vector<int> vec = { 1, 2, 3, 4, 5 };

    std::packaged_task<int(const vector<int>&)> pt(GetVectorMax);
    std::shared_future<int> s_fu(pt.get_future());

    std::thread t1(&PrintIntValueOnShared, ref(s_fu));
    std::thread t2(&PrintIntValueOnShared, ref(s_fu));
    std::thread t3(&PrintIntValueOnShared, ref(s_fu));

    

    std::thread(ref(pt), ref(vec)).join();

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}