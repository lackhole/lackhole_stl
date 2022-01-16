# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef SS_ITERATOR_H_
# define SS_ITERATOR_H_
#
# include "ss/detail/macro.h"
# include "ss/type_traits.h"

namespace ss {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct contiguous_iterator_tag : public random_access_iterator_tag {};

template<typename Iter>
struct iterator_traits;

template<typename T>
struct iterator_traits<T*> {
  static_assert(is_object<T>::value, "Type must be pointer to object");

  using difference_type = std::ptrdiff_t;
  using value_type = remove_cv_t<T>;
  using pointer = T*;
  using reference = T&;
  using iterator_category = random_access_iterator_tag;
  using iterator_concept = contiguous_iterator_tag;
};

namespace detail {

template<typename T, bool tag>
struct incrementable_traits_impl {};

template<typename T>
struct incrementable_traits_impl<T, true> {
  using difference_type = typename T::difference_type;
};

template<typename T>
struct incrementable_traits_impl<T*, true> {
  using difference_type = ptrdiff_t;
};

} //

// TODO: finish incrementable_traits
template<typename T>
struct incrementable_traits : detail::incrementable_traits_impl<T, detail::has_difference_type<T>::value> {};

template<typename T>
struct incrementable_traits<T*> : detail::incrementable_traits_impl<T*, is_object<T>::value> {};

template<typename T>
struct incrementable_traits<const T> : incrementable_traits<T> {};



namespace detail {

template<typename T, typename = void>
struct has_value_type : false_type {};
template<typename T>
struct has_value_type<T, void_t<typename T::value_type>> : true_type {};

template<typename It, bool v = incrementable<It>::value>
struct incrementable_iterator : false_type {};
template<typename It>
struct incrementable_iterator<It, true> : is_same<It&, decltype(++ss::declval<It&>())> {};

template<typename T, typename = void>
struct has_iterator_category : false_type {};
template<typename T>
struct has_iterator_category<T, void_t<typename T::iterator_category>> : true_type {};


template<typename It, bool v = has_iterator_category<iterator_traits<It>>::value>
struct is_random_access_iterator : false_type {};

template<typename It>
struct is_random_access_iterator<It, true>
  : is_base_of<random_access_iterator_tag, typename iterator_traits<It>::iterator_category> {};

template<typename It>
using LegacyIterator = conjunction<
  CopyConstructible<It>,
  CopyAssignable<It>,
  Destructible<It>,
  Swappable<It&>,
  has_value_type<iterator_traits<It>>,
  has_difference_type<iterator_traits<It>>,
  has_reference<iterator_traits<It>>,
  has_pointer<iterator_traits<It>>,
  has_pointer<iterator_traits<It>>,
  has_iterator_category<iterator_traits<It>>,
  dereferenceable<It>,
  incrementable_iterator<It>
>;

template<typename It,
  typename Reference = typename iterator_traits<It>::reference,
  typename ValueType = typename iterator_traits<It>::value_type,
  typename Expr = decltype(*ss::declval<It&>())>
using dereferenceable_iterator = conjunction<
  is_same<Expr, Reference>,
  is_convertible<Expr, ValueType>
>;


template<typename It,
  typename ValueType = typename iterator_traits<It>::value_type,
  bool v = post_incrementable<It>::value>
struct post_incrementable_iterator : false_type {};
template<typename It, typename ValueType>
struct post_incrementable_iterator<It, ValueType, true>
    : conjunction<is_same<It&, decltype(ss::declval<It&>()++)>> {};

template<typename It, bool v = conjunction<LegacyIterator<It>, EqualityComparable<It>>::value>
struct LegacyInputIterator : false_type {};

template<typename It>
struct LegacyInputIterator<It, true> : conjunction<
  NonEqualityComparable<It>,
  dereferenceable_iterator<It>,
  post_incrementable<It>
  > {};

} // namespace detail

/**
 * distance
 * @tparam InputIt
 * @param first
 * @param last
 * @return
 */
template<typename InputIt,
  enable_if_t<
    detail::is_random_access_iterator<InputIt>::value,
  int> = 0>
SS_CONSTEXPR_AFTER_14 typename iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last) {
  typename iterator_traits<InputIt>::difference_type d = 0;
  while (first != last) {
    ++first;
    ++d;
  }
  return d;
}

template<typename InputIt,
  enable_if_t<
    !detail::is_random_access_iterator<InputIt>::value,
  int> = 0>
constexpr typename iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last) {
  return last - first;
}


namespace detail {

template<typename Iter, typename D>
SS_CONSTEXPR_AFTER_14 void advance_impl(Iter& it, D n, random_access_iterator_tag) {
  it += n;
}

template<typename Iter, typename D>
SS_CONSTEXPR_AFTER_14 void advance_impl(Iter& it, D n, bidirectional_iterator_tag) {
  while (n > 0) {
    --n;
    ++it;
  }
  while (n < 0) {
    ++n;
    --it;
  }
}

template<typename Iter, typename D>
SS_CONSTEXPR_AFTER_14 void advance_impl(Iter& it, D n, input_iterator_tag) {
  SS_DEBUG_ASSERT(n >= 0,
                  "ss::advance : Distance must be equal or greater than 0 for input_iterator")
  while (n > 0) {
    ++it;
    --n;
  }
}

} // namespace detail


/**
 * advance
 * @tparam InputIt
 * @tparam Distance
 * @param it
 * @param n
 * @return
 */
template<typename InputIt, typename Distance>
SS_CONSTEXPR_AFTER_14 void advance(InputIt& it, Distance n) {
  detail::advance_impl(it, n, typename iterator_traits<InputIt>::iterator_category{});
}

// template<typename BidirIt>
// constexpr BidirIt prev(BidirIt it, typename iterator_traits<BidirIt>::difference_type n = 1) {
// 
// }

// TODO: Implement C++20
template<typename BidIter>
class reverse_iterator {
 public:
  using iterator_type     = BidIter;
  using iterator_category = typename iterator_traits<BidIter>::iterator_category;
  using value_type        = typename iterator_traits<BidIter>::value_type;
  using difference_type   = typename iterator_traits<BidIter>::difference_type;
  using pointer           = typename iterator_traits<BidIter>::pointer;
  using reference         = typename iterator_traits<BidIter>::reference;

  constexpr reverse_iterator() : current{} {}

  constexpr explicit reverse_iterator(iterator_type x) : current(x) {}

  template<typename U,
    enable_if_t<
      conjunction<
        negation<is_same<U, iterator_type>>
        // , concept convertible_to<const U&, iterator_type>
      >::value,
    int> = 0>
  constexpr reverse_iterator(const reverse_iterator<U>& other) : current(other.current) {}

  template<typename U,
    enable_if_t<
      conjunction<
        negation<is_same<U, iterator_type>>
        // convertible_to<const U&, iterator_type
        // assignable_from<Iter&, const U&>
      >::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 reverse_iterator& operator=(const reverse_iterator<U>& other) {
    current = other.current;
    return *this;
  }

  constexpr iterator_type base() const {
    return current;
  }

  SS_CONSTEXPR_AFTER_14 reference operator*() const {
    iterator_type tmp = current;
    return *--tmp;
  }

  constexpr pointer operator->() const {
    return get_ptr(is_pointer<iterator_type>{});
  }

 private:
  constexpr pointer get_ptr(true_type) const {
    return current - 1;
  }

  constexpr pointer get_ptr(false_type) const {
    return prev(current).operator->();
  }

  iterator_type current;
};



template<typename C>           constexpr auto begin(C& c)       -> decltype(c.begin()) { return c.begin(); }
template<typename C>           constexpr auto begin(const C& c) -> decltype(c.begin()) { return c.begin(); }
template<typename T, size_t N> constexpr T*   begin(T (&arr)[N])              noexcept { return arr; }
template<typename C> constexpr auto cbegin(const C& c) noexcept(noexcept(ss::begin(c))) -> decltype(ss::begin(c)) { return begin(c); }

template<typename C>           constexpr auto end(C& c)       -> decltype(c.end()) { return c.end(); }
template<typename C>           constexpr auto end(const C& c) -> decltype(c.end()) { return c.end(); }
template<typename T, size_t N> constexpr T*   end(T (&arr)[N])            noexcept { return arr + N; }
template<typename C> constexpr auto cend(const C& c) noexcept(noexcept(ss::end(c))) -> decltype(ss::end(c)) { return end(c); }

template<typename C>           constexpr auto rbegin(C& c)       -> decltype(c.rbegin()) { return c.rbegin(); }
template<typename C>           constexpr auto rbegin(const C& c) -> decltype(c.rbegin()) { return c.rbegin(); }
template<typename T, size_t N> constexpr reverse_iterator<T*> rbegin(T (&arr)[N])        { return reverse_iterator<T*>(arr + N); }
template<typename T> constexpr reverse_iterator<const T*> rbegin(std::initializer_list<T> il) { return reverse_iterator<const T*>(il.end()); }
template<typename C> constexpr auto crbegin(const C& c) noexcept(noexcept(ss::begin(c))) -> decltype(ss::rbegin(c)) { return rbegin(c); }

template<typename C>           constexpr auto rend(C& c)       -> decltype(c.rend()) { return c.rend(); }
template<typename C>           constexpr auto rend(const C& c) -> decltype(c.rend()) { return c.rend(); }
template<typename T, size_t N> constexpr reverse_iterator<T*> rend(T (&arr)[N])      { return reverse_iterator<T*>(arr); }
template<typename T> constexpr reverse_iterator<const T*> rend(std::initializer_list<T> il) { return reverse_iterator<const T*>(il.begin()); }
template<typename C> constexpr auto crend(const C& c) noexcept(noexcept(ss::end(c))) -> decltype(ss::rend(c)) { return rend(c); }

template<typename C>           constexpr auto   size(const C& c) -> decltype(c.size()) { return c.size(); }
template<typename T, size_t N> constexpr size_t size(T (&arr)[N])             noexcept { return N; }

template<typename C> constexpr auto ssize(const C& c)
-> common_type_t<ptrdiff_t, make_signed<decltype(c.size())>>
{
  using R = common_type_t<ptrdiff_t, make_signed<decltype(c.size())>>;
  return static_cast<R>(c.size());
}
template<typename T, size_t N> constexpr ptrdiff_t ssize(T (&arr)[N]) noexcept { return N; }

template<typename C>           SS_NODISCARD constexpr auto empty(const C& c)    -> decltype(c.empty()) { return c.empty(); }
template<typename T, size_t N> SS_NODISCARD constexpr bool empty(const T (&arr)[N])           noexcept { return false; }
template<typename T>           SS_NODISCARD constexpr bool empty(std::initializer_list<T> il) noexcept { return il.size() == 0; }

template<typename C>           constexpr auto data(C& c)           -> decltype(c.data()) { return c.data();   }
template<typename C>           constexpr auto data(const C& c)     -> decltype(c.data()) { return c.data();   }
template<typename T, size_t N> constexpr T*   data(T (&arr)[N])                 noexcept { return arr;        }
template<typename T>           constexpr T*   data(std::initializer_list<T> il) noexcept { return il.begin(); }

} // namespace ss

# endif // SS_ITERATOR_H_
