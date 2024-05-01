#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// 1.存取字符算法
//  at 和 [i]
void atDemo()
{
    string str = "12345";
    str[0] = '6';
    str.at(1) = '7';
    print(str);
}

// 2.插入与删除算法
// string& insert(int pos, const char* s);    插入字符串，从下标0开始
// string& insert(int pos, const string& str);插入字符串，从下标0开始
// string& insert(int pos, int n, char c);    在指定位置插入n个字符c
// string& erase(int pos, int n = npos);      删除从Pos开始的n个字符
void insertANDeraseDemo()
{
    string str = "hello";
    str.insert(1, "111");
    print(str);

    str.erase(1, 3);  //从1号位置开始3个字符
    print(str);
}

int main(int argc, char const* argv[])
{
    atDemo();
    insertANDeraseDemo();
    return 0;
}
