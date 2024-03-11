//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ALGORITHM_RANGES_FOLD_LEFT_HPP
#define LSD_ALGORITHM_RANGES_FOLD_LEFT_HPP

#include <functional>
#include <type_traits>
#include <utility>

#include "lsd/__concepts/assignable_from.h"
#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__concepts/invocable.h"
#include "lsd/__concepts/movable.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/is_invocable.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename F, typename T, typename I, typename U,
    bool = conjunction<
        movable<T>,
        movable<U>,
        convertible_to<T, U>,
        invocable<F&, U, iter_reference_t<I>>
    >::value /* true */>
struct indirectly_binary_left_foldable_impl
    : assignable_from<U&, invoke_result_t<F&, U, iter_reference_t<I>>> {};
template<typename F, typename T, typename I, typename U>
struct indirectly_binary_left_foldable_impl<F, T, I, U, false> : std::false_type {};

template<typename F, typename T, typename I,
    bool = invocable<F&, T, iter_reference_t<I>>::value /* true */>
struct indirectly_binary_left_foldable_2
    : conjunction<
          convertible_to<
              invoke_result_t<F&, T, iter_reference_t<I>>,
              std::decay_t<invoke_result_t<F&, T, iter_reference_t<I>>>>,
          indirectly_binary_left_foldable_impl<F, T, I, std::decay_t<invoke_result_t<F&, T, iter_reference_t<I>>>>
      >{};
template<typename F, typename T, typename I>
struct indirectly_binary_left_foldable_2<F, T, I, false> : std::false_type {};

template<typename F, typename T, typename I,
    bool = conjunction<
        copy_constructible<F>,
        indirectly_readable<I>,
        has_typename_type<iter_reference<I>>
    >::value /* true */ >
struct indirectly_binary_left_foldable : indirectly_binary_left_foldable_2<F, T, I> {};
template<typename F, typename T, typename I>
struct indirectly_binary_left_foldable<F, T, I, false> : std::false_type {};

struct fold_left_niebloid {
 private:
  template<typename R, typename T, typename F, bool = input_range<R>::value /* false */>
  struct check_range : std::false_type {};
  template<typename R, typename T, typename F>
  struct check_range<R, T, F, true>
      : indirectly_binary_left_foldable<F, T, iterator_t<R>> {};

 public:
  template<typename I, typename S, typename T, typename F, std::enable_if_t<conjunction<
      input_iterator<I>,
      sentinel_for<S, I>,
      indirectly_binary_left_foldable<F, T, I>
  >::value, int> = 0>
  constexpr auto operator()(I first, S last, T init, F f) const {
    using U = std::decay_t<invoke_result_t<F&, T, iter_reference_t<I>>>;

    if (first == last)
      return U(std::move(init));

    U accum = lsd::invoke(f, std::move(init), *first);
    for (++first; first != last; ++first) {
          accum = lsd::invoke(f, std::move(accum), *first);
    }

    return std::move(accum);
  }

  template<typename R, typename T, typename F, std::enable_if_t<check_range<R, T, F>::value, int> = 0>
  constexpr auto operator()(R&& r, T init, F f) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::move(init), std::ref(f));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::fold_left_niebloid fold_left{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_FOLD_LEFT_HPP
