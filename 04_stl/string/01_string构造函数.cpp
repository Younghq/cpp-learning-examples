#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// string数据类型 构造函数原型
// 1.string();                   默认构造，创建空字符串
// 2.string(const char * s);     使用字符串s初始化
// 3.string(const string & str); 使用string初始化当前string
// 4.string(int n,char c);       使用n个字符c初始化

int main()
{
    // 1.构造 空字符串
    string s1;
    print("s1:", s1);
    // 2.构造 c风格字符串
    const char* str = "hello world";
    string      s2(str);
    print(s2);

    // 3.构造 c风格字符数组
    char   buf[10] = "123456789";  // 常见socket编程
    string s3(buf);
    print(s3);

    // 4.拷贝构造 拷贝s2到s3
    string s4(s2);
    print(s4);

    // 5.构造 n个c字符
    char   c = '6';
    string s5(6, c);
    print(s5);
    return 0;
}