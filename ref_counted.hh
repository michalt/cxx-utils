#ifndef REF_COUNTED_HH
#define REF_COUNTED_HH

#include <cstddef>
#include <utility>

#include <boost/intrusive_ptr.hpp>

/* Note: this is not thread-safe. */

template <typename A, typename... Args>
boost::intrusive_ptr<A> make_intrusive(Args&& ...args) {
  return boost::intrusive_ptr<A>(new A(std::forward<Args>(args)...));
}

template <typename A>
class RefCounted {
  public:
    std::size_t Count() const { return ref_count_; }

    friend inline void intrusive_ptr_add_ref(const A *a) {
      ++a->ref_count_;
    }

    friend inline void intrusive_ptr_release(const A *a) {
      --a->ref_count_;
      if(a->ref_count_ == 0) {
        delete a;
      }
    }

  protected:
    /* All constructors should initialize the ref_count_ to zero.  Even the copy
     * constructors -- we create a new copy of the object and nothing points to
     * it. */

    RefCounted() : ref_count_(0) { }

    RefCounted(const RefCounted &rc) : ref_count_(0) { }

    RefCounted(RefCounted &&rc) : ref_count_(0) { }

    ~RefCounted() = default;

    /* Assignment should be a nop -- it changes the contents but not the number
     * of pointers that point to the object.  This is only important for derived
     * classes that have automatically generated operator=. */

    RefCounted &operator=(const RefCounted &rc) { return *this; }

    RefCounted &operator=(RefCounted &&rc) { return *this; }

  private:
    mutable std::size_t ref_count_;
};

#endif /* REF_COUNTED_HH */
