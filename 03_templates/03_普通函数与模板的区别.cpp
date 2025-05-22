#include <iostream>
using namespace std;

// 普通加法函数

int myAdd(int a, int b)
{
    return a + b;
}
// 模板加法函数
// 使用函数模板时，如果用自动类型推导，不会发生自动类型转换,即隐式类型转换
template <typename T>
T myAddtem(T &a, T &b)
{
    return a + b;
}

int main()
{
    int a = 3;
    int b = 10;
    char c = '1';
    cout << "myAdd(3, '1') = " << myAdd(a, c) << endl; // 1.存在隐式类型转换，将c转为ASCII码进行相加
    // cout  << myAddtem(a, c); 没有与参数列表匹配的 函数模板 "myAddtem" 实例
    cout << "myAdd(3, 10) = " << myAdd(a, b) << endl; // 2.不存在隐式类型转换
    return 0;
}