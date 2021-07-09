# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_UTILITY_H_
# define SS_UTILITY_H_
#
# include "ss/type_traits.h"

namespace ss {

template<typename T> // T = U (rvalue) T = U&(lvalue) where U is no-ref
constexpr inline T&& forward(remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template<typename T>
constexpr inline T&& forward(remove_reference_t<T>&& t) noexcept {
  static_assert(!is_lvalue_reference<T>::value, "Forwarding rvalue to lvalue is prohibited");
  return static_cast<T&&>(t);
}

template<typename T>
constexpr inline remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<remove_reference_t<T>&&>(t);
}

} // namespace ss

#endif // SS_UTILITY_H_
