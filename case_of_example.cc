#include <iostream>

#include "case_of.hh"

using namespace util;

int main(int argc, char *argv[]) {

  boost::variant<int, double, std::string> a{"foo"};
  boost::variant<int, double, std::string> b{10};
  boost::variant<int, double, std::string> c{10.5};

  std::cout << "- lambdas -" << std::endl;

  CaseOf(a
      , [](int x) { std::cout << x << std::endl; }
      , [](double x) { std::cout << x << std::endl; }
      , [](std::string x) { std::cout << x << std::endl; }
      );

  CaseOf(b
      , [](int x) { std::cout << x << std::endl; }
      , [](double x) { std::cout << x << std::endl; }
      , [](std::string x) { std::cout << x << std::endl; }
      );

  CaseOf(c
      , [](int x) { std::cout << x << std::endl; }
      , [](double x) { std::cout << x << std::endl; }
      , [](std::string x) { std::cout << x << std::endl; }
      );

  std::cout << "- visitor -" << std::endl;

  auto visitor = MakeVisitor(
        [](int x) { std::cout << x << std::endl; }
      , [](double x) { std::cout << x << std::endl; }
      , [](std::string x) { std::cout << x << std::endl; }
      );

  boost::apply_visitor(visitor, a);
  boost::apply_visitor(visitor, b);
  boost::apply_visitor(visitor, c);

  return EXIT_SUCCESS;
}
