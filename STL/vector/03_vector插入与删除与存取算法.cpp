#include <vector>
#include "../../toolfuc/print.hpp"
using namespace std;

// 插入删除
// push_back(ele);                                  // 尾部插入元素ele
// pop_back();                                      // 删除最后一个元素
// insert(const_iterator pos, ele);                 // 迭代器指向位置pos插入元素ele
// insert(const_iterator pos, int count,ele);       // 迭代器指向位置pos插入count个元素ele
// erase(const_iterator pos);                       // 删除迭代器指向的元素
// erase(const_iterator start, const_iterator end); // 删除迭代器从start到end之间的元素
// clear();                                         // 删除容器中所有元素
void insertAndDeleteMethodDemo()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    // 1.尾插法 push_back
    v1.push_back(6);
    v1.push_back(7);
    v1.push_back(8);
    print(v1);

    // 2.尾删法 pop_back
    v1.pop_back();
    print(v1);

    // 3.向迭代器位置插入元素
    v1.insert(v1.begin(), 3);
    print(v1);

    // 4.向迭代器位置插入若干数量的某元素，(注意数组越界)
    v1.insert(v1.begin(), 2, 1000);
    print(v1);

    // 1.删除迭代器指向的元素
    v1.erase(--v1.end());
    print(v1);

    // 2.删除迭代器范围内的元素
    v1.erase(v1.begin(), v1.end());
    // 3.清空
    v1.clear();
    print(v1);
}

// 数据存取
// at(int idx);     // 返回索引idx所指的数据
// operator[];      // 返回索引idx所指的数据
// front();         // 返回容器中第一个数据元素
// back();          // 返回容器中最后一个数据元素
void dataAccessMethodDemo()
{
    vector<string> v1 = {"第一个元素", "第二个元素", "最后一个元素"};
    print("v1.at(0)=", v1.at(0));
    print("v1[1]=", v1[1]);
    print("front()=", v1.front());
    print("back()=", v1.back());
}

int main(int argc, char* argv[])
{
    insertAndDeleteMethodDemo();
    dataAccessMethodDemo();
    return 0;
}
