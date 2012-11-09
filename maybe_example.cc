#include <iostream>
#include <cstdint>

#include "maybe.hh"

template <typename A>
struct Foo {
  Foo(const A &a) : a_(a + 1) {
    std::cout << "copy constructor: const &" << std::endl;
  }

  Foo(A &&a) : a_(a + 1) {
    std::cout << "copy constructor: &&" << std::endl;
  }

  ~Foo() {
    std::cout << "destructor" << std::endl;
  }

  A a_;
};

template <typename A>
std::ostream& operator<<(std::ostream &out, const Foo<A> &foo) {
  out << foo.a_;
  return out;
}

int main() {
  Maybe< Foo<uint64_t> > a;
  Maybe< Foo<uint64_t> > b{10};
  Maybe< Foo<uint64_t> > c{std::move(b)};

  std::cout << static_cast<bool>(a) << std::endl;
  std::cout << static_cast<bool>(b) << std::endl;
  // std::cout << *b << std::endl;
  std::cout << *c << std::endl;


  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(b) << std::endl;

}
