#include <iostream>
#include <string>
using namespace std;

// 在语法与用法上，与模板函数基本一致
// 注意事项:
// 1.C++标准规定，类模板可以设置类型的默认值，
// 而函数模板的模板参数列表中不能包含默认类型参数。
// 2.使用类模板，建议都显示指定类型，可以增强可读性。

// 包含两种类型的模板类
template <typename NameType,
          typename AgeType =
              int>  // 这里使用默认的类型int,在无法推导的请款修改

class Person {
private:
    NameType mName;
    AgeType  mAge;

public:
    Person(NameType name, AgeType age)
    {
        this->mName = name;
        this->mAge = age;
    }
    void showPerson()
    {
        cout << "name: " << this->mName << " age: " << this->mAge << endl;
    }
};

int main()
{
    // Person<string, int> p1("爹地", 999);
    Person p1("爹地", 999);
    p1.showPerson();
    return 0;
}