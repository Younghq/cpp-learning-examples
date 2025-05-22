#include <list>
#include "../../toolfuc/print.hpp"
using namespace std;

// 1.reverse();  // 反转链表
// 2.sort();     // 链表排序
// 自定义类型需要指定排序规则
// 1.在自定义类型中运用 重载小于运算符
class Person {
private:
    string name;
    int    age;

public:
    Person(string name, int age) : name(name), age(age) {}
    // 1.这是重载小于运算符定义排序规则做法，直接list.sort()即可通过年龄排序
    bool operator<(const Person& other) const
    {
        return age < other.age;
    }
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
};
// 2.定义并使用规则函数
bool compareByAge(const Person& p1, const Person& p2)
{
    return p1.getAge() < p2.getAge();
}

int main(int argc, char const* argv[])
{
    // 1.使用数据类型自定义的 operator< 运算符重载，实现sort内置排序
    list<Person> people = {{"rose", 21}, {"lisa", 26}, {"jenie", 23}};
    people.sort();
    for (auto Person : people) {
        print(Person.getAge(), Person.getName());
    }
    // 2.定义并使用规则函数
    list<Person> people2 = {{"bob", 9}, {"ken", 46}, {"jack", 29}};
    people.sort(compareByAge);
    for (auto Person : people) {
        print(Person.getAge(), Person.getName());
    }
    // 3.翻转
    people2.reverse();
    for (auto Person : people) {
        print(Person.getAge(), Person.getName());
    }
    return 0;
}
