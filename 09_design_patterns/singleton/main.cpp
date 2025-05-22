#include "01_singleton_lazy_cpp11.hpp"

int main(int argc, char const *argv[]) {
  SingletonLazy::GetInstance().Print();
  return 0;
}
