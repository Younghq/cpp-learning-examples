#include <list>
#include "../../toolfuc/print.hpp"
using namespace std;

//  1.给list容器进行赋值，以及交换list容器
//  assign(beg, end);                   // 将[beg, end)区间中的数据拷贝赋值给本身。
//  assign(n, elem);                    // 将n个elem拷贝赋值给本身。
//  list& operator=(const list &lst);   // 重载等号操作符
//  swap(lst);                          // 将lst与本身的元素互换。

//  2.对list容器的大小进行操作
//  size();                 // 返回容器中元素的个数
//  empty();                // 判断容器是否为空
//  resize(num);            // 重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
//  resize(num, elem);      // 重新指定容器的长度为num，若容器变长，则以elem值填充新位置。

void assignmentDemo()
{
    // 没啥好写的，注释说明一切
}
int main(int argc, char const* argv[])
{
    assignmentDemo();
    return 0;
}
