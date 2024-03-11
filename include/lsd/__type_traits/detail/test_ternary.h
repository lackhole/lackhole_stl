//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_TYPE_TRAITS_DETAIL_TEST_TERNARY_HPP_
#define LSD_TYPE_TRAITS_DETAIL_TEST_TERNARY_HPP_

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T1, typename T2, typename = void>
struct test_ternary_impl {};

template<typename T1, typename T2>
struct test_ternary_impl<T1, T2, void_t<decltype(false ? std::declval<T1>() : std::declval<T2>())>> {
  using type = decltype(false ? std::declval<T1>() : std::declval<T2>());
};

template<typename T1, typename T2>
struct test_ternary : test_ternary_impl<T1, T2> {};

template<typename T1, typename T2>
using test_ternary_t = typename test_ternary<T1, T2>::type;

} // namespace detail
} // namespace lsd

#endif // LSD_TYPE_TRAITS_DETAIL_TEST_TERNARY_HPP_
