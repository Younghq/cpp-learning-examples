#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

// 声明函数模板
template <typename T>
bool myCompare(T &p1, T &p2);

// 定义函数模板
template <typename T>
bool myCompare(T &p1, T &p2)
{
    return p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age;
}
// 模板特化的主要优点
// 1.性能优化，可以对特定类型或情况提供更搞笑的实现方式，从而提升代码性能
// 2.适应不同需求，且代码可以复用

// 模板特化的定义
template <>
bool myCompare(Person &p1, Person &p2)
{
    return p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age;
}

int main()
{
    Person p1("Alice", 25);
    Person p2("Bob", 30);

    if (myCompare(p1, p2))
    {
        cout << "Person相同,p1.m_Name = " << p1.m_Name << "\tp1.m.Age = " << p2.m_Age << endl;
    }
    else
    {
        cout << "Person不同,p1.m_Name = " << p1.m_Name << "\tp1.m.Age = " << p2.m_Age << endl;
    }

    return 0;
}
