//
// Created by cosge on 2023-12-25.
//

#ifndef LSD_ITERATOR_PREV_H_
#define LSD_ITERATOR_PREV_H_

#include <type_traits>

#include "lsd/__core/inline_variable.h"
#include "lsd/__iterator/bidirectional_iterator.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/advance.h"

namespace lsd {
namespace ranges {
namespace detail {

struct prev_niebloid {
  template<typename I>
  constexpr std::enable_if_t<bidirectional_iterator<I>::value, I>
  operator()(I i) const {
    --i;
    return i;
  }

  template<typename I>
  constexpr std::enable_if_t<bidirectional_iterator<I>::value, I>
  operator()(I i, iter_difference_t<I> n) const {
    ranges::advance(i, -n);
    return i;
  }


  template<typename I>
  constexpr std::enable_if_t<bidirectional_iterator<I>::value, I>
  operator()(I i, iter_difference_t<I> n, I bound) const {
    ranges::advance(i, -n, bound);
    return i;
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_VARIABLE constexpr detail::prev_niebloid prev{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_ITERATOR_PREV_H_
