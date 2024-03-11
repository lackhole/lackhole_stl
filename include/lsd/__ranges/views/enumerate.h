//
// Created by yonggyulee on 2024/01/22.
//

#ifndef LSD_RANGES_VIEWS_ENUMERATE_HPP
#define LSD_RANGES_VIEWS_ENUMERATE_HPP

#include <type_traits>
#include <tuple>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/enumerate_view.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

template<template<typename...> class Tuple>
class enumerate_adaptor_closure : public range_adaptor_closure<enumerate_adaptor_closure<Tuple>> {
  public:
  enumerate_adaptor_closure() = default;

  template<typename R, std::enable_if_t<viewable_range<R>::value, int> = 0>
  constexpr auto operator()(R&& r) const {
    return enumerate_view<all_t<R>, Tuple>(std::forward<R>(r));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::enumerate_adaptor_closure<std::tuple> enumerate{};

LSD_INLINE_OR_STATIC constexpr detail::enumerate_adaptor_closure<std::pair> enumerate_pair{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_ENUMERATE_HPP
