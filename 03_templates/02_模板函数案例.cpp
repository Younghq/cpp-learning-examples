#include <iostream>
using namespace std;

// 交换的函数模板
template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 打印数组的模板
template <class T>
void printArr(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// 排序的模板
template <class T>
void mySort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i; // 选择排序
        for (int j = i + 1; j < len; j++)
        {
            if (arr[max] > arr[j])
            {
                max = j;
            }
        }
        if (max != i)
        {
            mySwap(arr[max], arr[i]);
        }
    }
    printArr(arr, len); // 调用打印数组函数
}

// template <class T> 是较早版本的 C++ 标准中使用的形式，但从语义上讲，class 这个关键字在这里并不是指类（class）的意思，而是泛型（generic）的意思，用来表示模板参数类型。
// template <typename T> 使用 typename 这个关键字来表示模板参数的类型，更加符合直觉上的理解。

int main()
{
    int arr[] = {2, 7, 1, 9, 5};
    mySort(arr, 5);
    return 0;
}
