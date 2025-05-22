#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// string字符串拼接函数原型：
// string& operator+=(const char* str); //重载+=操作符
// string& operator+=(const char c); //重载+=操作符
// string& operator+=(const string& str); //重载+=操作符
// string& append(const char *s);  //把字符串s连接到当前字符串结尾
// string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾
// string& append(const string &s); //同operator+=(const string& str)
// string& append(const string &s, int pos, int n);//字符串s中从pos开始的n个字符连接到字符串结尾

int main(int argc, char const* argv[])
{
    string str1 = "我";
    str1 += "是";
    print(str1);
    string str2 = "一个coder";
    str1 += str2;
    print(str1);
    string str3 = "I";
    str3.append(" love ");
    str3.append("game abcde", 4);
    str3.append("abcde", 0, 3);  // 从第0个开始，追加3个字符，到str3的末尾
    cout << "str3 = " << str3 << endl;
    return 0;
}
