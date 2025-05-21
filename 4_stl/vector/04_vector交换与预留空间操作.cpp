#include <vector>
#include "../../toolfuc/print.hpp"
using namespace std;
// 1.交换
// swap可以使两个容器互换，可以达到实用的收缩内存效果
// swap(vec);        // 将vec与本身的元素互换
void swapDemo()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {5, 4, 3, 2, 1};
    print("交换前:", "\n1 2 3 4 5"
                     "\n5 4 3 2 1");
    v1.swap(v2);
    print("交换后:");
    print(v1);
    print(v2);
}

// 2.空间预留
// 适用于数据量较大，可以一开始利用reserve预留空间
// reserve(int len); //容器预留len个元素长度，预留位置不初始化，元素不可访问。
void reserveDemo()
{
    vector<int> v1;

    //预留空间
    v1.reserve(100);
    v1.insert(v1.begin(), 1000, 1000);
    print(v1);
}

int main(int argc, char const* argv[])
{
    swapDemo();
    reserveDemo();
    return 0;
}
