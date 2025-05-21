#include <string>
#include "../../toolfuc/print.hpp"
using namespace std;

// 1.查找算法
// find 从左到右查找
//  int find(const string& str, int pos = 0) const; // 查找str第一次出现位置
//  int find(const char* s, int pos = 0) const;     // 查找s第一次出现位置
//  str，s 被查找的字符串，pos，开始查找的位置
// rfind 从右到左查找

void findDemo()
{
    //查找
    string str1 = "abcdefgde";

    int pos = str1.find("de");

    if (pos == -1) {
        cout << "未找到" << endl;
    } else {
        cout << "pos = " << pos << endl;
    }

    pos = str1.rfind("de");

    cout << "pos = " << pos << endl;
}

// 2.替换算法
//  string& replace(int pos, int n, const string& str);
//  string& replace(int pos, int n,const char* s);
// pos起始位，n替换字符数量，str被替换的字符串，s被替换的c风格串
void replaceDemo()
{
    //替换
    string str1 = "abcdefgde";
    // 这里替换的字符串字符为4，大于3，则会变成a1111efgde
    str1.replace(1, 3, "1111");

    cout << "str1 = " << str1 << endl;
}

// 3.比较算法
//  int compare(const string &s) const; //与字符串s比较
//  int compare(const char *s) const; //与字符串s比较
// 等于0，大于1，小于-1
// 通常用于判断两串是否相等，大小意义不大
void compareDemo()
{
    string s1 = "hello";
    string s2 = "aello";

    int ret = s1.compare(s2);

    if (ret == 0) {
        cout << "s1 等于 s2" << endl;
    } else if (ret > 0) {
        cout << "s1 大于 s2" << endl;
    } else {
        cout << "s1 小于 s2" << endl;
    }
}

int main(int argc, char const* argv[])
{
    findDemo();
    replaceDemo();
    compareDemo();
    return 0;
}
