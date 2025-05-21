#include <iostream>
using namespace std;

void printArr(int *point) {
  cout << "数组：";

  for (int *ptr = point; ptr < point + 5; ++ptr) {
    cout << *ptr << " ";
  }
  cout << endl;
}

/*
演示几种指针数组地址操作：
arrPoint:0x55555556aed0
数组：1 2 3 4 5
*arrPoint:1
数组：1 2 3 4 5
arrPoint++:0x55555556aed0
数组：2 3 4 5 0
++arrPoint:0x55555556aed4
数组：2 3 4 5 0
arrPoint+1:0x55555556aed4
数组：1 2 3 4 5
*(arrPoint++):1
数组：2 3 4 5 0
*(arrPoint + 1):2
数组：1 2 3 4 5
*(++arrPoint):2
数组：2 3 4 5 0
*/

int main() {
  // new 用于申请memory分配 成功返回一个指针地址
  int *intPoint = new int;    // 分配一个int 4字节
  int *arrPoint = new int[5]; // 分配一个5* int 4*5 字节

  int values[] = {1, 2, 3, 4, 5}; // 一种快速初始化arrPoint指针数组的方式
  copy(values, values + 5, arrPoint);

  // 打印数组内容

  int *temparrPoint = arrPoint;
  // 演示几种指针数组地址操作
  cout << "演示几种指针数组地址操作：" << endl;
  cout << "arrPoint:" << arrPoint << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 优先级 ()优先于 ++ -- 优先于 *
  cout << "*arrPoint:" << *arrPoint << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 后缀运算符++：先返回移动前的地址，再往后移动1个类型字节（改变原始指针位置）
  cout << "arrPoint++:" << arrPoint++ << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // ++前缀运算符：先往后移动一个类型字节（改变原始指针位置），再返回移动后的地址
  cout << "++arrPoint:" << ++arrPoint << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 指针算数运算：生成一个新的指针值，指向arrPoint+1的位置
  cout << "arrPoint+1:" << arrPoint + 1 << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  /// 后缀递增运算符++：先返回递增前的地址，再递增arrPoint地址（改变原始指针位置），*再取出递增前的地址的值
  cout << "*(arrPoint++):" << *(arrPoint++) << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 指针算术运算：根据括号优先级，先将arrPoint指针移动1个类型字节，然后返回递增后的指针值
  cout << "*(arrPoint + 1):" << *(arrPoint + 1) << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 前缀运算符：根据括号优先级，会先将arrPoint指针递增（改变原始指针位置），然后返回递增后的指针值
  cout << "*(++arrPoint):" << *(++arrPoint) << endl;
  printArr(arrPoint);
  arrPoint = temparrPoint;

  // 释放内存
  delete intPoint;
  delete[] arrPoint;

  return 0;
}
