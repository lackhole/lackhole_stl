//
// Created by YongGyu Lee on 3/14/24.
//

#ifndef LSD_EXPECTED_UNEXPECTED_HPP_
#define LSD_EXPECTED_UNEXPECTED_HPP_

#include <type_traits>
#include <utility>

#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_swappable.h"
#include "lsd/__type_traits/is_specialization.h"
#include "lsd/__type_traits/negation.h"
#include "lsd/__type_traits/remove_cvref.h"
#include "lsd/__utility/in_place.h"

namespace lsd {

template<typename E>
class unexpected {
 public:
  static_assert(std::is_object<E>::value, "Constraints not satisfied");
  static_assert(!std::is_array<E>::value, "Constraints not satisfied");
  static_assert(!std::is_const<E>::value, "Constraints not satisfied");
  static_assert(!std::is_volatile<E>::value, "Constraints not satisfied");
  static_assert(!is_specialization<E, unexpected>::value, "Constraints not satisfied");

  constexpr unexpected(const unexpected&) = default;
  constexpr unexpected(unexpected&&) = default;

  template<typename Err = E, std::enable_if_t<conjunction<
      negation<std::is_same<remove_cvref_t<Err>, unexpected>>,
      negation<std::is_same<remove_cvref_t<Err>, in_place_t>>,
      std::is_constructible<E, Err>
  >::value, int> = 0>
  constexpr explicit unexpected(Err&& e)
      : error_(std::forward<Err>(e)) {}

  template<typename... Args, std::enable_if_t<
      std::is_constructible<E, Args...>
  ::value, int> = 0>
  constexpr explicit unexpected(in_place_t, Args&&... args)
      : error_(std::forward<Args>(args)...) {}

  template<typename U, typename... Args, std::enable_if_t<
      std::is_constructible<E, std::initializer_list<U>&, Args...>
  ::value, int> = 0>
  constexpr explicit unexpected(in_place_t, std::initializer_list<U> il, Args&&... args)
      : error_(il, std::forward<Args>(args)...) {}

  constexpr unexpected& operator=(const unexpected&) = default;
  constexpr unexpected& operator=(unexpected&&) = default;

  constexpr const E& error() const& noexcept {
    return error_;
  }
  constexpr E& error() & noexcept {
    return error_;
  }
  constexpr const E&& error() const&& noexcept {
    return std::move(error_);
  }
  constexpr E&& error() && noexcept {
    return std::move(error_);
  }

  template<typename E2 = E, std::enable_if_t<is_swappable<E2>::value, int> = 0>
  constexpr void swap(unexpected& other) noexcept(is_nothrow_swappable<E>::value) {
    using std::swap;
    swap(error(), other.error());
  }

  template<typename E2, std::enable_if_t<equality_comparable<E2>::value, int> = 0>
  friend constexpr bool operator==(unexpected& x, unexpected<E2>& y) {
    return x.error() == y.error();
  }

  template<typename E2, std::enable_if_t<equality_comparable<E2>::value, int> = 0>
  friend constexpr bool operator!=(unexpected& x, unexpected<E2>& y) {
    return !(x == y);
  }

  // TODO: Implement friend swap

 private:
  E error_;
};

#if __cplusplus >= 201703L

template<typename E>
unexpected(E) -> unexpected<E>;

#endif

} // namespace lsd

#endif // LSD_EXPECTED_UNEXPECTED_HPP_
