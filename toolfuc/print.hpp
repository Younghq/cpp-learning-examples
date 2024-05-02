#pragma once
#include <iostream>
#include <vector>
using namespace std;

/// @brief 打印
/// @tparam ...Args
/// @param ...args
template <typename... Args>
void print(Args... args)
{
    (cout << ... << args) << endl;
}

/// @brief 打印向量数组元素
/// @tparam T
/// @param v
template <typename T>
void print(vector<T>& v)
{
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}
