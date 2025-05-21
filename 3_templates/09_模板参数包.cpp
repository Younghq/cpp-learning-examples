#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename... Args>
void printArgs(Args... args)
{
    (cout << ... << args) << endl;
}

// 使用模板参数包 Args，不需要额外指定返回类型 T
template <typename... Args>
auto add(Args... args)
{
    // 使用折叠表达式展开参数包，对所有参数进行加法操作，并自动推导返回类型
    return (args + ...);
}

template <typename... Args>
void print(Args... args)
{
    (cout << ... << args) << endl;
}

int main()
{
    printArgs(1, 2, 3, 4, 5);
    cout << add(1, 2, 3, 4, 5) << endl;
    print(6, 7, 8, 9, '10');
    return 0;
}

// 这一段是从
// https://learn.microsoft.com/zh-cn/cpp/cpp/ellipses-and-variadic-templates?view=msvc-170的例子，摘录的
// void print()
// {
//     cout << endl;
// }

// template <typename T>
// void print(const T& t)
// {
//     cout << t << endl;
// }

// template <typename First, typename... Rest>
// void print(const First& first, const Rest&... rest)
// {
//     cout << first << ", ";
//     print(rest...);
// }
// int main()
// {
//     print();
//     print(1);

//     print(10, 20);
//     print(100, 200, 300);
//     print("first", 2, "third", 3.14159);
// }