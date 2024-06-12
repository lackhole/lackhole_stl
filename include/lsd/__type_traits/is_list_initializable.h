//
// Created by YongGyu Lee on 11/3/23.
//

#ifndef LSD_TYPE_TRAITS_IS_LIST_INITIALIZABLE_H_
#define LSD_TYPE_TRAITS_IS_LIST_INITIALIZABLE_H_

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {

namespace detail {

template<typename To, typename From, typename = void>
struct is_list_initializable_impl : std::false_type {};

template<typename To, typename From>
struct is_list_initializable_impl<To, From, void_t<decltype(To{std::declval<From>()})>> : std::true_type {};

} // namespace detail

template<typename To, typename From>
struct is_list_initializable : detail::is_list_initializable_impl<To, From> {};

template<typename To, typename From>
using is_list_initializable_t = typename is_list_initializable<To, From>::type;

template<typename To, typename From>
struct is_copy_list_initializable : std::conditional_t<is_list_initializable<To, From>::value, std::is_convertible<From, To>, std::false_type> {};

template<typename To, typename From>
using is_copy_list_initializable_t = typename is_copy_list_initializable<To, From>::type;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_LIST_INITIALIZABLE_H_