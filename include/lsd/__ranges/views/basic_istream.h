//
// Created by yonggyulee on 2/3/24.
//

#ifndef LSD_RANGES_VIEWS_BASIC_ISTREAM_HPP
#define LSD_RANGES_VIEWS_BASIC_ISTREAM_HPP

#include <type_traits>

#include "lsd/__concepts/derived_from.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/views/basic_istream_view.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

template<typename T, typename = void>
struct has_typename_char_type : std::false_type {};
template<typename T>
struct has_typename_char_type<T, void_t<typename T::char_type>> : std::true_type {};

template<typename T, typename = void>
struct has_typename_traits_type : std::false_type {};
template<typename T>
struct has_typename_traits_type<T, void_t<typename T::traits_type>> : std::true_type {};

template<typename U, bool = conjunction<has_typename_char_type<U>, has_typename_traits_type<U>>::value /* false */>
struct derived_from_basic_istream : std::false_type {};
template<typename U>
struct derived_from_basic_istream<U, true>
    : derived_from<U, std::basic_istream<typename U::char_type, typename U::traits_type>> {};

template<typename T>
struct basic_istream_niebloid {
  template<typename E, std::enable_if_t<
      derived_from_basic_istream<std::remove_reference_t<E>
  >::value, int> = 0>
  constexpr auto operator()(E&& e) const {
    using U = std::remove_reference_t<decltype(e)>;
    return basic_istream_view<T, typename U::char_type, typename U::traits_type>(std::forward<E>(e));
  }
};

} // namespace detail

template<typename T>
LSD_INLINE_OR_STATIC constexpr detail::basic_istream_niebloid<T> istream{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_BASIC_ISTREAM_HPP
