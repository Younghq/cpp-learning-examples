#include <iostream>
#include <string>
using namespace std;

template <typename NameType, typename AgeType = int>
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

// 1.这里接受模板类作为参数(引用)
void printPerson(Person<string, int>& p)
{
    p.showPerson();
}
// 2.参数模板化
template <typename T1, typename T2>
void printPerson2(Person<T1, T2>& p)
{
    cout << "T1的类型为： " << typeid(T1).name() << endl;
    cout << "T2的类型为： " << typeid(T2).name() << endl;

    p.showPerson();
}
// 3.全类模板化
template <typename T>
void printPerson3(T& p)
{
    cout << "T的类型为： " << typeid(T).name() << endl;
    p.showPerson();
}

// 第二种方式需要显式指定模板参数类型，因此在调用函数时需要明确传入类型信息，比如
// printPerson2<string, int>(prn2);。
// 第三种方式则利用了自动类型推导，使用auto关键字可以让编译器根据传入参数的类型自动推导模板参数，使得调用函数更加简洁，比如
// printPerson3(prn3);。

int main()
{
    // 演示1
    Person<string, int> prn1("queen", 38);
    printPerson(prn1);

    // 演示2
    Person<string, int> prn2("king", 40);
    printPerson2<string, int>(prn2);

    // 演示3
    Person<string, int> prn3("king", 40);
    printPerson3(prn3);
    return 0;
}
