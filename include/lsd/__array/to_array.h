//
// Created by YongGyu Lee on 4/11/24.
//

#ifndef LSD_ARRAY_TO_ARRAY_HPP_
#define LSD_ARRAY_TO_ARRAY_HPP_

#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace lsd {
namespace detail {

template<typename T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>) {
  return {{a[I]...}};
}

template<typename T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl(T (&&a)[N], std::index_sequence<I...>) {
  return {{std::move(a[I])...}};
}

} // namespace detail

template<typename T, std::size_t N, std::enable_if_t<std::is_constructible<T, T&>::value && !std::is_array<T>::value, int> = 0>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) {
  return lsd::detail::to_array_impl(a, std::make_index_sequence<N>{});
}

template<typename T, std::size_t N, std::enable_if_t<std::is_move_constructible<T>::value && !std::is_array<T>::value, int> = 0>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&&a)[N]) {
  return lsd::detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}

} // namespace lsd

#endif // LSD_ARRAY_TO_ARRAY_HPP_
