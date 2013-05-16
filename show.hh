#pragma once

#include <sstream>
#include <string>

// FIXME: This should be:
// template <typename A>
// struct Show {
//   std::string operator()(const A &a) {
//     std::stringstream s;
//     s << a;
//     return std::move(s.str());
//   }
// };

template <typename A>
std::string Show(const A &a) {
  std::stringstream s;
  s << a;
  return std::move(s.str());
}
