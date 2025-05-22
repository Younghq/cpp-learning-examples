#include <iostream>
using namespace std;

// 模板交换函数
template <typename T>
void mySwap(T &a, T &b) // 1.模板提供自动类型推导，但必须参数类型统一
{                       // 2.模板也提供显示指定类型，mySwap<int>(a,b)
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void noneTem()
{
    cout << "空参数模板函数也要指定类型" << endl;
}

int main()
{
    auto a = 1, b = 2;
    cout << "原本的值："
         << "a:" << a << " "
         << "b:" << b << endl;

    // 1.自动类型推导用法
    mySwap(a, b);
    cout << "自动推导："
         << "a:" << a << " "
         << "b:" << b << endl;

    // 2.显示指定类型用法
    mySwap<int>(a, b);
    cout << "显示指定："
         << "a:" << a << " "
         << "b:" << b << endl;

    // 注意事项
    // 1.自动类型推导,要求参数的T数据类型一致
    // 2.不论什么模板必须要确定T的数据类型,才可以使用.

    auto str = "123";
    // mySwap(str, a);  err:参数类型不一致
    // noneTem();       err:空参数列表的模板函数也要指定类型
    noneTem<int>();
    return 0;
}
