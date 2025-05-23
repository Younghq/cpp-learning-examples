// #include "01_singleton_lazy_cpp11.hpp"

// int main(int argc, char const *argv[]) {
//   SingletonLazy::GetInstance().Print();
//   return 0;
// }

#include "02_singleton_eager_cpp11.hpp"

int main(int argc, char const *argv[]) {
  SingletonEager::GetInstance().Print();
  return 0;
}
