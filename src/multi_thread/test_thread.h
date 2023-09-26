#include <iostream>
#include <boost/thread.hpp>

using namespace std;
static void outFileThreadFunc(int k) {
    cout << "Hello, outFileThreadFunc!" <<k<<endl;
}   