#include<iostream>
#include<memory>
#include<algorithm>


using namespace std;


int main(){
    auto add = [](int a,int b)->int{return a+b;};
    int sum = add(1,2);
    // auto print_sum=[](){cout<<"sum= "<<sum<<endl;}; //lambda格式问题
    auto print_sum=[=](){cout<<"sum= "<<sum<<endl;};
    auto print_sumC=[&](){sum=0;cout<<"sum= "<<sum<<endl;};
    print_sum();
    print_sumC();
    return 0;
}