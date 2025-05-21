#include <iostream>

int main() {
  using namespace std;

  // & 取地址运算符
  int age = 30;
  const double Pi = 3.1416;

  cout << "age地址：" << &age << endl;
  cout << "Pi地址：" << &Pi << endl;

  auto p_age = &age;
  auto p_Pi = &Pi;

  // * 解引用运算符
  cout << "p_age值：" << *p_age << endl;
  cout << "p_Pi值：" << *p_Pi << endl;

  // 指针类型大小 32位系统与64位系统分别为 4byte 8byte
  cout << "指针类型大小:" << sizeof(p_Pi) << endl;
  return 0;
}