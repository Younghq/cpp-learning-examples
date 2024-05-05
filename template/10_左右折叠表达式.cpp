#include <iostream>
#include "../toolfuc/print.hpp"
using namespace std;
// 可以参考这篇博客，https://zhxilin.github.io/post/tech_stack/1_programming_language/modern_cpp/cpp17/fold_expressions/
// 展开运算符 ...
// 折叠表达式分为四种
//  1. 一元左折叠 (... op pack)
//  2. 一元右折叠 (pack op ...)
//  3. 二元左折叠 (init op ... op pack)
//  4. 二元右折叠 (pack op ... op init)

// 一元左折叠
template <typename... Args>
auto sumL(Args... args)  // 参数包展开(递归)
{
    return (... + args);
}

// 一元右折叠
template <typename... Args>
auto sumR(Args... args)  // 参数包展开(递归)
{
    return (args + ...);
}

//一元右折叠
template <typename... T>
void printR(T... args)
{
    ((cout << args << ", "), ...) << endl;
}

//一元左折叠 (... op pack)
template <typename... T>
void printL(T... args)
{
    (..., (cout << args << ", ")) << endl;
    //...展开运算符，op是逗号，E是输出语句
}

int main()
{
    print("sumL=", sumL(1, 2, 3, 4, 5));
    print("sumR=", sumR(1, 2, 3, 4, 5));
    printR("hello", "zhxilin", 1, 2, 3);
    printL("hello", "zhxilin", 1, 2, 3);
    return 0;
}
