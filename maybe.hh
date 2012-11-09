#ifndef MAYBE_HH
#define MAYBE_HH

#include <cassert>
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

    Maybe(const Maybe<A> &ma) : is_just_(ma.is_just_) {
      if (is_just_) {
        new (storage_) A{*ma};
      }
    }

    Maybe(Maybe<A> &&ma) : is_just_(ma.is_just_) {
      if (is_just_) {
        new (storage_) A{std::move(*ma)};
      }
      ma.is_just_ = false;
    }

    template <typename B, typename C, typename... Rest>
    Maybe(B &&b, C &&c, Rest &&... rest) : is_just_(true) {
      new (&storage_) A{std::forward<B>(b), std::forward<C>(c),
        std::forward<Rest>(rest)...};
    }

    ~Maybe() {
      if (is_just_) {
        (**this).~A();
      }
    }

    Maybe<A>& operator=(const Maybe<A> &rhs) {
      if (rhs.is_just_) {
        is_just_ = true;
        **this = *rhs;
      } else {
        is_just_ = false;
      }
    }

    Maybe<A>& operator=(Maybe<A> &&rhs) {
      if (rhs.is_just_) {
        is_just_ = true;
        **this = std::move(*rhs);
        rhs.is_just_ = false;
      } else {
        is_just_ = false;
      }
    }

    operator bool() const {
      return is_just_;
    }

    const A& operator*() const {
      assert(is_just_);
      return *static_cast<const A*>(static_cast<const void*>(storage_));
    }

    A& operator*() {
      assert(is_just_);
      return *static_cast<A*>(static_cast<void*>(storage_));
    }


  private:
    bool is_just_;
    std::uint8_t storage_[sizeof(A)];
};

#endif /* MAYBE_HH */
