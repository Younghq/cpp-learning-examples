#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// 1.求子串算法
// string substr(int pos = 0, int n = npos) const;
// 返回由pos开始的n个字符组成的字符串
void substrDemo()
{
    string str = "abcdefg";
    string subStr = str.substr(1, 3);
    print("subStr = ", subStr);

    // 分隔邮箱后缀与用户名案例
    string email = "hello@sina.com";
    int    pos = email.find("@");            // find查找@所在位置
    string username = email.substr(0, pos);  // 求出从0->@位置的串
    print("username: ", username);           // 打印用户名
}

int main(int argc, char const* argv[])
{
    substrDemo();
    return 0;
}
