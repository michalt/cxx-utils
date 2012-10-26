#ifndef MAYBE_HH
#define MAYBE_HH

#include <cstdint>
#include <utility>

template <typename A>
class Maybe {
  public:
    Maybe() : is_just_(false) {}

    Maybe(const A &a) : is_just_(true) {
      new (storage_) A{a};
    }

    Maybe(A &&a) : is_just_(true) {
      new (storage_) A{std::move(a)};
    }

    template <typename B, typename C, typename... Rest>
    Maybe(B &&b, C &&c, Rest &&... rest) : is_just_(true) {
      new (&storage_) A{std::forward<B>(b), std::forward<C>(c),
        std::forward<Rest>(rest)...};
    }

    operator bool() const {
      return is_just_;
    }

    // const A& operator*() const {
      // return *static_cast<A*>(static_cast<void*>(&storage_));
    // }

    A& operator*() {
      return *static_cast<A*>(static_cast<void*>(&storage_));
    }


  private:
    bool is_just_;
    std::uint8_t storage_[sizeof(A)];
};

#endif /* MAYBE_HH */
