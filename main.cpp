#include <iostream>
#include "dynamic_bitset.hpp"

int main() {
  std::cout << "Hello, World!" << std::endl;
  dynamic_bitset bitset(17);
  bitset[0] = true;
  bitset[1] = false;
  bitset[2] = true;
  bitset[3] = false;
  bitset[4] = true;
  bitset[5] = false;
  bitset[6] = true;
  bitset[7] = false;
  bitset[8] = true;
  bitset[9] = false;
  bitset.resize(10);
  std::cout << bitset.size() << '\n' << bitset.capacity() << '\n';
  std::cout << std::boolalpha << bitset[0] << '\n';
  std::cout << std::noboolalpha << bitset << '\n';
  bitset.resize(100);
  std::cout << bitset.size() << '\n' << bitset.capacity() << '\n';
  bitset.resize(10);
  std::cout << bitset.size() << '\n' << bitset.capacity() << '\n';
  bitset.clear();
  std::cout << bitset.size() << '\n' << bitset.capacity() << '\n';
  return 0;
}
