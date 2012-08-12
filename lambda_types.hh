#ifndef LAMBDA_TYPES_HH
#define LAMBDA_TYPES_HH

namespace {
  struct EmptyType;
}

template <typename T>
struct LambdaTypes_;

template <typename R, typename C, typename A>
struct LambdaTypes_<R (C::*)(A)> {
  typedef A FirstArgumentType;
  typedef EmptyType SecondArgumentType;
  typedef R ReturnType;
};

template <typename R, typename C, typename A>
struct LambdaTypes_<R (C::*)(A) const> {
  typedef A FirstArgumentType;
  typedef EmptyType SecondArgumentType;
  typedef R ReturnType;
};

template <typename R, typename C, typename A, typename B>
struct LambdaTypes_<R (C::*)(A, B)> {
  typedef A FirstArgumentType;
  typedef B SecondArgumentType;
  typedef R ReturnType;
};

template <typename R, typename C, typename A, typename B>
struct LambdaTypes_<R (C::*)(A, B) const> {
  typedef A FirstArgumentType;
  typedef B SecondArgumentType;
  typedef R ReturnType;
};

template <typename L>
struct LambdaTypes {
  typedef typename LambdaTypes_<decltype(&L::operator())>::FirstArgumentType
    FirstArgumentType;
  typedef typename LambdaTypes_<decltype(&L::operator())>::SecondArgumentType
    SecondArgumentType;
  typedef typename LambdaTypes_<decltype(&L::operator())>::ReturnType
    ReturnType;
};

#endif /* LAMBDA_TYPES_HH */
