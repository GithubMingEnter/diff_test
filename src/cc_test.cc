#include <iostream>

#include <boost/noncopyable.hpp>
#include<spdlog/spdlog.h>
#include<stdio.h>
#include <memory>
class Test1 {
    public:
    int i_;
    Test1(int i):i_(i) {std::cout << "This is Test1 that is copyable" << std::endl;}
    inline const int getI() const{
        return i_;
    }
};

class Test2 : boost::noncopyable {
    public:
    Test2(int i) {std::cout << "This is Test2 that is noncopyable" << std::endl;}
};
void test_nocopyable()
{
        Test1 t1(1);
    Test2 t2(2);

    Test1 t3 = t1;    // It's OK
    Test1 t4(t1);     // It's OK
    std::cout<<t1.getI()<<std::endl;

    // Test2 t5 = t2;    // Cannot be referenced
    // Test2 t6(t2);     // Cannot be referenced
    Test2 &t7 = t2;   // It's OK
}
void multi_point()
{
    int *p=nullptr;
    int pi=114514;
    p=&pi;

    int **p2=&p;
    /* &（*p2）=&p=p2  &(**p2)=*p2=&(*p)=&(pi) 一个& 一个*可以抵消  */
    
}
struct MyClass {
    int value;
    MyClass(int v) : value(v) {}
    ~MyClass() { std::cout << "MyClass destroyed\n"; }
};
int test_sharedPtr() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(10);
    std::shared_ptr<MyClass> ptr2 = ptr1; // ptr2 also points to the same object
    std::cout << "ptr1 points to value: " << ptr1->value << "\n";
    std::cout << "ptr2 points to value: " << ptr2->value << "\n";
    return 0;
}
int main()
{
    multi_point();
    test_sharedPtr();
    return 0;
}




