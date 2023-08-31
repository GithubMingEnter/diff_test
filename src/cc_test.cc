#include <iostream>

#include <boost/noncopyable.hpp>
#include<spdlog/spdlog.h>
#include<stdio.h>
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
    printf("*p={%d},pi={%d},&p={%d},&(*p)={%d}\n",*p,pi,&p,&(*p));

    int **p2=&p;
    printf("**p2={%d},&(*p2)={%d},p2={%d},&(p2)={%d},&(**p2)={%d}\n",**p2,&(*p2),p2,&(p2),&(**p2));
    /* &（*p2）=&p=p2  &(**p2)=*p2=&(*p)=&(pi) 一个& 一个*可以抵消  */
    
}

int main()
{
    multi_point();

    return 0;
}
