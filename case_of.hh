#ifndef CASE_OF_HH
#define CASE_OF_HH

#include <utility>

#include <boost/variant.hpp>

#include "lambda_types.hh"


using namespace util;

namespace {

template <typename... Rest>
struct Visitor_;

template <typename ReturnType>
struct Visitor_<ReturnType> {
  Visitor_() { }

  template <typename T>
  ReturnType operator()(T t) const {
    (void) t;
    static_assert(std::is_same<T, T>::value == false,
        "You need to specify a lambda for _all_ possible types!\
        You're missing case for T.");
  }
};

template <typename ReturnType, typename Head, typename... Tail>
struct Visitor_<ReturnType, Head, Tail...> : public Visitor_<ReturnType, Tail...> {

  Visitor_(Head &&f, Tail&&... tail)
    : Visitor_<ReturnType, Tail...>(std::forward<Tail>(tail)...),
      fun(std::forward<Head>(f)) { }

  ReturnType operator()(
      const typename LambdaTypes<Head>::FirstArgumentType &a) const {
    return fun(a);
  }

  template <typename A>
  ReturnType operator()(A a) const {
    return Visitor_<ReturnType, Tail...>::operator()(a);
  }

  Head fun;
};

template <typename... Rest>
struct Visitor2_;

template <typename ReturnType>
struct Visitor2_<ReturnType> {
  Visitor2_() { }

  template <typename T, typename U>
  ReturnType operator()(T t, T u) const {
    (void) t;
    (void) u;
    static_assert(std::is_same<T, T>::value == false,
        "You need to specify a lambda for _all_ possible types!\
        You're missing case for T and U.");
  }
};

template <typename ReturnType, typename Head, typename... Tail>
struct Visitor2_<ReturnType, Head, Tail...> : public Visitor2_<ReturnType, Tail...> {

  Visitor2_(Head &&f, Tail&&... tail)
    : Visitor2_<ReturnType, Tail...>(std::forward<Tail>(tail)...),
      fun(std::forward<Head>(f)) { }

  ReturnType operator()(
      const typename LambdaTypes<Head>::FirstArgumentType &a,
      const typename LambdaTypes<Head>::SecondArgumentType &b) const {
    return fun(a, b);
  }

  template <typename A, typename B>
  ReturnType operator()(A a, B b) const {
    return Visitor2_<ReturnType, Tail...>::operator()(a, b);
  }

  Head fun;
};

}  /* anonymous namespace */


namespace util {

template <typename Head, typename... Tail>
struct Visitor
    : public boost::static_visitor<typename LambdaTypes<Head>::ReturnType>
    , public Visitor_<typename LambdaTypes<Head>::ReturnType, Head, Tail...> {
  Visitor(Head &&fun, Tail&&... tail)
    : Visitor_<typename LambdaTypes<Head>::ReturnType, Head, Tail...>(
        std::forward<Head>(fun), std::forward<Tail>(tail)...) { }
};


template <typename Head, typename... Tail>
struct Visitor2
    : public boost::static_visitor<typename LambdaTypes<Head>::ReturnType>
    , public Visitor2_<typename LambdaTypes<Head>::ReturnType, Head, Tail...> {
  Visitor2(Head &&fun, Tail&&... tail)
    : Visitor2_<typename LambdaTypes<Head>::ReturnType, Head, Tail...>(
        std::forward<Head>(fun), std::forward<Tail>(tail)...) { }
};

template <typename... Lambdas>
Visitor<Lambdas...> MakeVisitor(Lambdas&&... lambdas) {
  return Visitor<Lambdas...>{std::forward<Lambdas>(lambdas)...};
}

template <typename... Lambdas>
Visitor<Lambdas...> MakeVisitor2(Lambdas&&... lambdas) {
  return Visitor2<Lambdas...>{std::forward<Lambdas>(lambdas)...};
}

template <typename V, typename Head, typename... Tail>
typename LambdaTypes<Head>::ReturnType CaseOf(const V &variant, Head&& head,
    Tail&&... tail) {
  Visitor<Head, Tail...> visitor{std::forward<Head>(head),
    std::forward<Tail>(tail)...};
  return boost::apply_visitor(visitor, variant);
}

template <typename V, typename Head, typename... Tail>
typename LambdaTypes<Head>::ReturnType CaseOf2(const V &variant1, const V &variant2,
    Head&& head, Tail&&... tail) {
  Visitor2<Head, Tail...> visitor{std::forward<Head>(head),
    std::forward<Tail>(tail)...};
  return boost::apply_visitor(visitor, variant1, variant2);
}

}  /* namespace util */

#endif /* CASE_OF_HH */
