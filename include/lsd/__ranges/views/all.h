//
// Created by yonggyulee on 2023/12/29.
//

#ifndef LSD_RANGES_VIEWS_ALL_HPP
#define LSD_RANGES_VIEWS_ALL_HPP

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/owning_view.h"
#include "lsd/__ranges/range.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/ref_view.h"
#include "lsd/__ranges/view.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__type_traits/detail/return_category.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

using lsd::detail::return_category;

class all_adaptor_closure : public range_adaptor_closure<all_adaptor_closure> {
  template<typename T>
  using return_category_type =
      std::conditional_t<
          view<std::decay_t<T>>::value, return_category<1, std::decay_t<T>>,
      std::conditional_t<
          conjunction<
              range<std::remove_reference_t<T>>,
              std::is_object<std::remove_reference_t<T>>,
              std::is_lvalue_reference<T>
          >::value,
              return_category<2, ref_view<std::remove_reference_t<T>>>,
              return_category<3, owning_view<std::remove_reference_t<T>>>
      >>;

  template<typename R, typename T>
  constexpr T operator()(R&& r, return_category<1, T>) const {
    return std::forward<R>(r);
  }

  template<typename R, typename T>
  constexpr T operator()(R&& r, return_category<2, T>) const {
    return {std::forward<R>(r)}; // ref_view
  }

  template<typename R, typename T>
  constexpr T operator()(R&& r, return_category<3, T>) const {
    return {std::forward<R>(r)}; // owning_view
  }

 public:
  all_adaptor_closure() = default;

  template<typename R>
  constexpr typename return_category_type<R&&>::return_type
  operator()(R&& r) const {
    return (*this)(std::forward<R>(r), return_category_type<R&&>{});
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::all_adaptor_closure all{};

} // inline namespace niebloid

namespace detail {

template<typename R, bool = viewable_range<R>::value /* true */>
struct all_t_impl {
  using type = decltype(views::all(std::declval<R>()));
};

template<typename R>
struct all_t_impl<R, false> {};

} // namespace detail

template<typename R>
using all_t = typename detail::all_t_impl<R>::type;

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_ALL_HPP
