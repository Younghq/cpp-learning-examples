#include <iostream>
#include <string>
using namespace std;

void myPrint(int a, int b)
{
    cout << "调用的普通函数" << endl;
}

template <typename T>
void myPrint(T a, T b)
{
    cout << "调用的函数模板" << endl;
}

template <typename T>
void myPrint(T a, T b, T c)
{
    cout << "调用重载的模板" << endl;
}

// 调用规则如下：
// 1. 如果函数模板和普通函数都可以实现，优先调用普通函数
// 2. 可以通过空模板参数列表来强制调用函数模板
// 3. 函数模板也可以发生重载
// 4. 如果函数模板可以产生更好的匹配,优先调用函数模板
// 总结：既然提供了函数模板，最好就不要提供普通函数，否则容易出现二义性

int main()
{
    int a = 1, b = 2, c = 3;
    char c1 = '1', c2 = '2';

    myPrint(a, b);    // 1.当普通函数与模板函数同存，优先调用普通函数
    myPrint<>(a, b);  // 2.同存时，可以显式<>强制调用模板函数
    myPrint(a, b, c); // 3.模板函数也可以重载
    myPrint(c1, c2);  // 4.如果模板可以产生更好的匹配，则优先函数模板
    return 0;         // 总结，实现一样的功能，要么函数，要么模板，同存有可能会产生二义性
}