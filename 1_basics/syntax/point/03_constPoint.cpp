#include <iostream>
using namespace std;

// 案例：使用const引用确保被调用的函数不能被修改按引用传入的值
void Square(const int &number, int &result) {
  result = number * number;
  // number = 1； 常量无法修改

  /* const int &number：这表示传递了一个对整数值的常量引用。它的意义在于：
  使用引用的方式传递参数，这意味着函数内部对参数的修改会影响到函数外部传入的变量。
  const
  关键字表示在函数内部不能修改引用所绑定的值，因此函数内部无法修改参数的值。 */
}

int main() {
  cout << "输入两数相乘的数字:" << endl;
  int num = 0;
  cin >> num;
  int res = 0;
  Square(num, res);
  cout << "num：" << num << " res" << res << endl;
  return 0;
}

// inherit