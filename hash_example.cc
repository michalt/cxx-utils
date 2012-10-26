#include <iostream>

#include "hash.hh"

int main() {
  std::tuple<int, std::string, double> foo = {1, "foo", 3.5};
  std::hash< std::tuple<int, std::string, double> > hasher;
  std::cout << hasher(foo) << std::endl;

  std::size_t h = 0;
  hash_combine(h, std::get<0>(foo));
  hash_combine(h, std::get<1>(foo));
  hash_combine(h, std::get<2>(foo));
  std::cout << h << std::endl;
}
