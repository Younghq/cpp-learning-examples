#include <vector>
#include "../../toolfuc/print.hpp"
using namespace std;

// empty();                 // 判断容器是否为空
// capacity();              // 容器的容量
// size();                  // 返回容器中元素的个数
// resize(int num);         // 重新指定容器的长度为num，若容器变长，则以默认值填充新位置。//如果容器变短，则末尾超出容器长度的元素被删除。
// resize(int num, elem);   // 重新指定容器的长度为num，若容器变长，则以elem值填充新位置。//如果容器变短，则末尾超出容器长度的元素被删除
int main(int argc, char const* argv[])
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    print(v1.empty() ? "vector 为空" : "vector 不为空");
    print("vector 容量= ", v1.capacity());
    print("vector 实际元素个数= ", v1.capacity());
    v1.resize(10);
    print("vector 重新设置容量10后的容量= ", v1.capacity());
    return 0;
}
