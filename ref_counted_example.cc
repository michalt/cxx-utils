#include "ref_counted.hh"

using namespace util;

struct Foo : public RefCounted<Foo> {
  Foo(int i) : x(i) { }

  void Debug() {
    std::cout << this << " : " << x << " : " << RefCounted::Count() << std::endl;
  }

  int x;
};


int main() {
  std::cout << "- 1" << std::endl;

  boost::intrusive_ptr<Foo> foo = make_intrusive<Foo>(100);
  foo->Debug();

  std::cout << "- 2" << std::endl;

  boost::intrusive_ptr<Foo> bar = foo;
  foo->Debug();
  bar->Debug();

  std::cout << "- 3" << std::endl;

  bar = make_intrusive<Foo>(*foo);
  ++bar->x;
  foo->Debug();
  bar->Debug();

  std::cout << "- 4" << std::endl;

  boost::intrusive_ptr<Foo> foobar = make_intrusive<Foo>(300);

  *foobar = *foo;
  foo->Debug();
  bar->Debug();
  foobar->Debug();

  std::cout << "- 5" << std::endl;

  foobar = foo;
  foo->Debug();
  bar->Debug();
  foobar->Debug();

  // not possible:
  // std::cout << foo->ref_count_ << std::endl;
}

