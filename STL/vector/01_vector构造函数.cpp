#include <vector>
#include "../../toolfuc/print.hpp"
using namespace std;

// vector<T> v;                 // 采用模板实现类实现，默认构造函数
// vector(v.begin(), v.end());  // 将v[begin(), end())区间中的元素拷贝给本身。
// vector(n, elem);             // 构造函数将n个elem拷贝给本身。
// vector(const vector &vec);   // 拷贝构造函数。

int main(int argc, char const* argv[])
{
    // 1.无参构造
    vector<int> v1;
    v1 = {1, 2, 3, 4, 5};
    // 2.范围拷贝构造
    vector<int> v2(v1.begin(), v1.end());  // begin() end() 为迭代器
    print(v2);
    // 3.拷贝n个数量的elem构造
    vector<int> v3(10, 1);
    print(v3);
    // 4.拷贝构造
    vector<int> v4(v3);
    print(v4);
    return 0;
}
