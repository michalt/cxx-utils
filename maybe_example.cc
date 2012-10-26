#include <iostream>
#include <cstdint>

#include "maybe.hh"

int main() {
  Maybe<uint64_t> a;
  Maybe<uint64_t> b{10};

  std::cout << static_cast<bool>(a) << std::endl;
  std::cout << static_cast<bool>(b) << std::endl;
  std::cout << *b << std::endl;


  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(b) << std::endl;

}
