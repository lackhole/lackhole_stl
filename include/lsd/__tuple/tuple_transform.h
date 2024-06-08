//
// Created by YongGyu Lee on 2/20/24.
//

#ifndef LSD_TUPLE_TUPLE_TRANSFORM_H_
#define LSD_TUPLE_TUPLE_TRANSFORM_H_

#include <tuple>
#include <utility>

#include "lsd/__functional/invoke.h"
#include "lsd/__type_traits/bool_constant.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<typename Tuple, typename F, std::size_t... I>
constexpr auto tuple_transform_impl(Tuple&& t, F&& f, std::index_sequence<I...>)
    noexcept(conjunction<
        bool_constant<noexcept(lsd::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))))>...
    >::value)
{
  return std::tuple<decltype(lsd::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))))...>(
      lsd::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t)))...);
}

} // namespace detail

template<typename Tuple, typename F>
constexpr auto tuple_transform(Tuple&& t, F&& f)
    noexcept(noexcept(
        detail::tuple_transform_impl(
            std::forward<Tuple>(t),
            std::forward<F>(f),
            std::make_index_sequence<std::tuple_size<remove_cvref_t<Tuple>>::value>{}
        )
    ))
{
  return detail::tuple_transform_impl(
      std::forward<Tuple>(t), std::forward<F>(f),
      std::make_index_sequence<std::tuple_size<remove_cvref_t<Tuple>>::value>{});
}

} // namespace lsd

#endif // LSD_TUPLE_TUPLE_TRANSFORM_H_
