#ifndef HASH_HH
#define HASH_HH

#include <map>
#include <set>
#include <tuple>
#include <vector>

template <typename A>
inline void hash_combine(std::size_t &seed, const A &v);

namespace {

template <std::size_t I, typename T>
struct tuple_hash : public tuple_hash<I - 1, T> {
  static void hash(std::size_t &seed, const T &tuple) {
    tuple_hash<I - 1, T>::hash(seed, tuple);
    hash_combine(seed, std::get<I>(tuple));
  }
};

template <typename T>
struct tuple_hash<0, T> {
  static void hash(std::size_t &seed, const T &tuple) {
    hash_combine(seed, std::get<0>(tuple));
  }
};

} /* anonymous namespace */

namespace std {

  template<typename A, typename B>
  struct hash< std::pair<A, B> > {
    inline std::size_t operator()(const std::pair<A, B> &pair) const {
      std::size_t h = 0;
      hash_combine(h, pair.first);
      hash_combine(h, pair.second);
      return h;
    }
  };

  template<typename... Types>
  struct hash< std::tuple<Types...> > {
    inline std::size_t operator()(const std::tuple<Types...> &tuple) const {
      std::size_t h = 0;
      tuple_hash< std::tuple_size< std::tuple<Types...> >::value - 1,
        std::tuple<Types...> >::hash(h, tuple);
      return h;
    }
  };

  template<typename A>
  struct hash< std::vector<A> > {
    inline std::size_t operator()(const std::vector<A> &vec) const {
      std::size_t h = 0;
      for (auto &x : vec) {
        hash_combine(h, x);
      }
      return h;
    }
  };

  template<typename A, typename B>
  struct hash< std::map<A, B> > {
    inline std::size_t operator()(const std::map<A, B> &map) const {
      std::size_t h = 0;
      for (auto &x : map) {
        hash_combine(h, x);
      }
      return h;
    }
  };

  template<typename A, typename B>
  struct hash< std::set<A, B> > {
    inline std::size_t operator()(const std::set<A, B> &set) const {
      std::size_t h = 0;
      for (auto &x : set) {
        hash_combine(h, x);
      }
      return h;
    }
  };

}

/* Taken from Boost. */
template <typename A>
inline void hash_combine(std::size_t &seed, const A &a) {
  std::hash<A> hash_value;
  seed ^= hash_value(a) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

#endif /* HASH_HH */
