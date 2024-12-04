#include <iostream>
#include <memory>
#include <utility>

// 自定义 make_shared 实现，采用单一内存分配
template <typename T, typename... Args>
std::shared_ptr<T> make_shared(Args&&... args) {
    // 分配足够的内存来存放对象和控制块
    void* rawMemory = operator new(sizeof(T) + sizeof(std::shared_ptr<T>)); // 这里的控制块大小只是示意

    // 在分配的内存上构造对象
    T* obj = new (rawMemory) T(std::forward<Args>(args)...);

    return std::shared_ptr<T>(obj);
}

// 测试类
class MyClass {
public:
    MyClass(int x, double y) : a(x), b(y) {
        std::cout << "MyClass constructed with a = " << a << ", b = " << b << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructed" << std::endl;
    }

private:
    int a;
    double b;
};

int main() {
    // 使用自定义的 make_shared 创建 MyClass 的实例
    auto obj = make_shared<MyClass>(42, 3.14);

    // 使用实例
    return 0;
}