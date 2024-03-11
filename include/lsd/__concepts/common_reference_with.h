//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_COMMON_REFERENCE_WITH_HPP_
#define LSD_CONCEPTS_COMMON_REFERENCE_WITH_HPP_

#include <type_traits>

#include "lsd/__concepts/convertible_to.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/common_reference.h"

namespace lsd {
namespace detail {

template<
    typename T,
    typename U,
    bool = conjunction<
               has_typename_type<common_reference<T, U>>,
               has_typename_type<common_reference<U, T>>
           >::value /* false */
>
struct common_reference_with_impl : std::false_type {};

template<typename T, typename U>
struct common_reference_with_impl<T, U, true>
    : conjunction<
        same_as< common_reference_t<T, U>, common_reference_t<U, T> >,
        convertible_to<T, common_reference_t<T, U> >,
        convertible_to<U, common_reference_t<T, U> >
      > {};

} // namespace detail

template<typename T, typename U>
struct common_reference_with : detail::common_reference_with_impl<T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_COMMON_REFERENCE_WITH_HPP_
