#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// 赋值的函数原型：
// string& operator=(const char* s);    // char*类型字符串赋值给当前的字符串
// string& operator=(const string &s);  // 把字符串s赋给当前的字符串
// string& operator=(char c);           // 字符赋值给当前的字符串
// string& assign(const char *s);       // 把字符串s赋给当前的字符串
// string& assign(const char *s, int n);// 把字符串s的前n个字符赋给当前的字符串
// string& assign(const string &s);     // 把字符串s赋给当前字符串
// string& assign(int n, char c);       // 用n个字符c赋给当前字符串

int main()
{
    // 推荐使用 operator= 运算符重载
    string str1;
    str1 = "我是str1";
    print(str1);

    string str2;
    str2 = str1;
    print(str1, ",str2拷贝str1");

    string str3;
    str3 = 'c';
    print(str3, ",str3拷贝了'c'");

    // 下面几种了解即可

    string str4;
    str4.assign("hello c++");
    print(str4);

    string str5;
    str5.assign("hello c++", 5);  // 只拷5个字符
    print(str5);

    string str6;
    str6.assign(str5);
    print(str6);

    string str7;
    str7.assign(5, 'x');
    print(str7);
    return 0;
}