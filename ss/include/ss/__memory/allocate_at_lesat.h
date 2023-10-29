//
// Created by cosge on 2023-10-29.
//

#ifndef SS___MEMORY_ALLOCATE_AT_LESAT_H_
#define SS___MEMORY_ALLOCATE_AT_LESAT_H_

#include <cstddef>

#include "ss/__memory/allocator.h"
#include "ss/__memory/allocator_traits.h"
#include "ss/__type_traits/integral_constant.h"
#include "ss/__type_traits/void_t.h"
#include "ss/type_traits.h"
#include "ss/__utility/declval.h"

namespace ss {

namespace detail {

template<typename T, typename X = allocator<T>>
struct is_allocator_completeness : conjunction<
    is_complete<X>,
    is_complete<typename allocator_traits<X>::allocator_type>,
    is_complete<typename allocator_traits<X>::value_type>,
    is_complete<typename allocator_traits<X>::pointer>,
    is_complete<typename allocator_traits<X>::const_pointer>,
    is_complete<typename allocator_traits<X>::void_pointer>,
    is_complete<typename allocator_traits<X>::const_void_pointer>,
    is_complete<typename allocator_traits<X>::difference_type>,
    is_complete<typename allocator_traits<X>::size_type>,
    is_complete<typename allocator_traits<X>::propagate_on_container_copy_assignment>,
    is_complete<typename allocator_traits<X>::propagate_on_container_move_assignment>,
    is_complete<typename allocator_traits<X>::propagate_on_container_swap>,
    is_complete<typename allocator_traits<X>::is_always_equal>
> {};

template<typename Alloc, typename = void>
struct has_allocate_at_least : false_type {};

template<typename Alloc>
struct has_allocate_at_least<Alloc,
                             void_t<decltype(ss::declval<Alloc>().allocate_at_least(size_t{}))>> : true_type {};

template<typename Alloc>
constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least_impl(Alloc& a, size_t n, true_type) {
  return a.allocate_at_least(n);
}

template<typename Alloc>
constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least_impl(Alloc& a, size_t n, false_type) {
  return {a.allocate(n), n};
}

} // namespace detail

/**
 * allocate_at_least
 */
template<typename Alloc>
SS_NODISCARD constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least(Alloc& a, size_t n) {
  return detail::allocate_at_least_impl(detail::has_allocate_at_least<Alloc>{});
}

} // namespace ss

#endif // SS___MEMORY_ALLOCATE_AT_LESAT_H_
