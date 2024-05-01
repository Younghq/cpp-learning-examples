#include <iostream>
#include <string>
using namespace std;
// 类模板碰到继承，需要注意一下几点
// 1.如果子类模板继承的父类也是一个模板，则需要显式的指定父类T的类型。
// 2.如果不指定，编译器无法给子类分配内存。
// 3.如果想灵活指定父类的T类型,则子类也要是模板。
template <typename T>
class Base {
    T m;
};

template <typename T>
class son : public Base<int> {
    son()
    {
        cout << "" << endl;
    }
};

int main()
{
    return 0;
}