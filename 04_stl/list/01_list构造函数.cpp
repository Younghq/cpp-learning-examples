#include <list>
#include "../../toolfuc/print.hpp"
using namespace std;

//  list，双向动态链表容器
//  list<T> lst;            // list采用采用模板类实现,对象的默认构造形式：
//  list(beg,end);          // 构造函数将[beg, end)区间中的元素拷贝给本身。
//  list(n,elem);           // 构造函数将n个elem拷贝给本身。
//  list(const list &lst);  // 拷贝构造函数。

int main(int argc, char const* argv[])
{
    // 1.空构造
    list<int> l1;
    l1.push_back(1);  // push_back 尾插
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    print(l1);
    // 2.迭代器范围拷贝构造
    list<int> l2(l1.begin(), l1.end());
    print(l2);
    // 3.拷贝构造
    list<int> l3(l2);
    print(l3);
    // 4.n个elem拷贝构造
    list<int> l4(10, 1000);
    print(l4);

    return 0;
}
