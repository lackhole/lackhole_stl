# /*
#  * Created by YongGyu Lee on 2021/06/25.
#  */
#
# ifndef SS_TYPE_TRAITS_H_
# define SS_TYPE_TRAITS_H_
#
# include <cstddef>
#
# include "ss/detail/macro.h"

/*
integral_constant                 (C++11)
bool_constant                     (C++17)

true_type	std::integral_constant<bool, true>
false_type	std::integral_constant<bool, false>

is_void                             (C++11)
is_null_pointer                     (C++14)
is_integral                         (C++11)
is_floating_point                   (C++11)
is_array                            (C++11)
is_enum                             (C++11)
is_union                            (C++11)
is_class                            (C++11)
is_function                         (C++11)
is_pointer                          (C++11)
is_lvalue_reference                 (C++11)
is_rvalue_reference                 (C++11)
is_member_object_pointer            (C++11)
is_member_function_pointer          (C++11)

Composite type categories
is_fundamental                      (C++11)
is_arithmetic                       (C++11)
is_scalar                           (C++11)
is_object                           (C++11)
is_compound                         (C++11)
is_reference                        (C++11)
is_member_pointer                   (C++11)

Type properties
is_const                            (C++11)
is_volatile                         (C++11)
is_trivial                          (C++11)
is_trivially_copyable               (C++11)
is_standard_layout                  (C++11)
is_pod                              (C++11)(deprecated in C++20)
is_literal_type                     (C++11)(deprecated in C++17)(removed in C++20)
has_unique_object_representations   (C++17)
is_empty                            (C++11)
is_polymorphic                      (C++11)
is_abstract                         (C++11)
is_final                            (C++14)
is_aggregate                        (C++17)
is_signed                           (C++11)
is_unsigned                         (C++11)
is_bounded_array                    (C++20)
is_unbounded_array                  (C++20)
is_scoped_enum                      (C++23)

Supported operations
is_constructible                    (C++11)
is_trivially_constructible          (C++11)
is_nothrow_constructible            (C++11)
is_default_constructible            (C++11)
is_trivially_default_constructible  (C++11)
is_nothrow_default_constructible    (C++11)
is_copy_constructible               (C++11)
is_trivially_copy_constructible     (C++11)
is_nothrow_copy_constructible       (C++11)
is_move_constructible               (C++11)
is_trivially_move_constructible     (C++11)
is_nothrow_move_constructible       (C++11)
is_assignable                       (C++11)
is_trivially_assignable             (C++11)
is_nothrow_assignable               (C++11)
is_copy_assignable                  (C++11)
is_trivially_copy_assignable        (C++11)
is_nothrow_copy_assignable          (C++11)
is_move_assignable                  (C++11)
is_trivially_move_assignable        (C++11)
is_nothrow_move_assignable          (C++11)
is_destructible                     (C++11)
is_trivially_destructible           (C++11)
is_nothrow_destructible             (C++11)
has_virtual_destructor              (C++11)
is_swappable_with                   (C++17)
is_swappable                        (C++17)
is_nothrow_swappable_with           (C++17)
is_nothrow_swappable                (C++17)

Property queries
alignment_of                        (C++11)
rank                                (C++11)
extent                              (C++11)
is_same                             (C++11)
is_base_of                          (C++11)
is_convertible                      (C++11)
is_nothrow_convertible              (C++20)
is_layout_compatible                (C++20)
is_pointer_interconvertible_base_of (C++20)
is_invocable                        (C++17)
is_invocable_r                      (C++17)
is_nothrow_invocable                (C++17)
is_nothrow_invocable_r              (C++17)

Const-volatility specifiers
remove_cv                           (C++11)
remove_const                        (C++11)
remove_volatile                     (C++11)
add_cv                              (C++11)
add_const                           (C++11)
add_volatile                        (C++11)

References
remove_reference                    (C++11)
add_lvalue_reference                (C++11)
add_rvalue_reference                (C++11)

Pointers
remove_pointer                      (C++11)
add_pointer                         (C++11)

Sign modifiers
make_signed                         (C++11)
make_unsigned                       (C++11)

Arrays
remove_extent                       (C++11)
remove_all_extents                  (C++11)

Miscellaneous transformations
aligned_storage                     (C++11)
aligned_union                       (C++11)
decay                               (C++11)
remove_cvref                        (C++20)
enable_if                           (C++11)
conditional                         (C++11)
common_type                         (C++11)
underlying_type                     (C++11)
result_of                           (C++11)(removed in C++20)
invoke_result                       (C++17)
void_t                              (C++17)
type_identity                       (C++20)

Operations on traits
conjunction                         (C++17)
disjunction                         (C++17)
negation                            (C++17)

Functions
Member relationships
is_pointer_interconvertible_with_class  (C++20)
is_corresponding_member                 (C++20)

Constant evaluation context
is_constant_evaluated                   (C++20)
 */

namespace ss {

template<typename T, T v>
struct integral_constant {
  using value_type = T;
  using type = integral_constant;

  SS_INLINE_VAR static constexpr value_type value = v;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = integral_constant<bool, true >;
using false_type = integral_constant<bool, false>;

template<typename ...> struct always_false : false_type {};
template<typename ...> struct always_true : true_type {};



/**
 * type_identity
 * @tparam T
 */
template<typename T> struct type_identity { using type = T; };
template<typename T> using type_identity_t = typename type_identity<T>::type;



namespace detail {
template<typename T> auto type_t_test(int) -> type_identity<typename T::type>;
template<typename T> auto type_t_test(...) -> type_identity<T>;
}

/**
 * type_t
 * @tparam T
 */
template<typename T>
using type_t = typename decltype(detail::type_t_test<T>(0))::type;



/**
 * void_t
 */
template<typename ...>
using void_t = void;



/**
 * enable_if
 * @tparam b
 * @tparam T
 */
template<bool b, typename T = void> struct enable_if          {};
template<typename T>                struct enable_if<true, T> { using type = T; };
template<bool b, typename T = void> using enable_if_t = typename enable_if<b, T>::type;



/**
 * conditional
 * @tparam b
 * @tparam If
 * @tparam Then
 */
template<bool b, typename If, typename Then> struct conditional { using type = If; };
template<typename If, typename Then>         struct conditional<false, If, Then> { using type = Then; };
template<bool b, typename If, typename Then> using conditional_t = typename conditional<b, If, Then>::type;



/**
 * is_const
 * @tparam T
 */
template<typename T> struct is_const          : false_type {};
template<typename T> struct is_const<const T> : true_type  {};
template<typename T> SS_INLINE_VAR constexpr bool is_const_v = is_const<T>::value;



/**
 * is_volatile
 * @tparam T
 */
template<typename T> struct is_volatile             : false_type {};
template<typename T> struct is_volatile<volatile T> : true_type  {};
template<typename T> SS_INLINE_VAR constexpr bool is_volatile_v = is_volatile<T>::value;



/**
 * is_same
 * @tparam T
 */
template<typename T, typename U> struct is_same       : false_type {};
template<typename T>             struct is_same<T, T> : true_type {};
template<typename T, typename U> using is_same_t = typename is_same<T, U>::type;
template<typename T, typename U> SS_INLINE_VAR constexpr bool is_same_v = is_same<T, U>::value;



/**
 * is_not_same
 * @tparam T
 */
template<typename T, typename U> struct is_not_same       : true_type  {};
template<typename T>             struct is_not_same<T, T> : false_type {};
template<typename T, typename U> using is_not_same_t = typename is_not_same<T, U>::type;
template<typename T, typename U> SS_INLINE_VAR constexpr bool is_not_same_v = is_not_same<T, U>::value;



/**
 * remove_const
 * @tparam T
 */
template<typename T> struct remove_const          { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> using remove_const_t = typename remove_const<T>::type;



/**
 * remove_volatile
 * @tparam T
 */
template<typename T> struct remove_volatile             { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };
template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;



/**
 * remove_cv
 * @tparam T
 */
template<typename T> struct remove_cv                   { using type = T; };
template<typename T> struct remove_cv<const T>          { using type = T; };
template<typename T> struct remove_cv<volatile T>       { using type = T; };
template<typename T> struct remove_cv<const volatile T> { using type = T; };
template<typename T> using remove_cv_t = typename remove_cv<T>::type;



/**
 * add_const
 * @tparam T
 */
template<typename T> struct add_const { using type = const T; };
template<typename T> using add_const_t = typename add_const<T>::type;



/**
 * add_volatile
 * @tparam T
 */
template<typename T> struct add_volatile { using type = volatile T; };
template<typename T> using add_volatile_t = typename add_volatile<T>::type;



/**
 * add_cv
 * @tparam T
 */
template<typename T> struct add_cv { using type = const volatile T; };
template<typename T> using add_cv_t = typename add_cv<T>::type;



/**
 * remove_reference
 * @tparam T
 */
template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };
template<typename T> using remove_reference_t = typename remove_reference<T>::type;



namespace detail {
template<typename T>
auto try_add_lvalue_reference(int) -> type_identity<T&>;

template<typename T>
auto try_add_lvalue_reference(...) -> type_identity<T>;

template<typename T>
struct is_lvalue_referencable : is_not_same<type_identity<T>, decltype(try_add_lvalue_reference<T>(0))> {};

template<typename T>
auto try_add_rvalue_reference(int) -> type_identity<T&&>;

template<typename T>
auto try_add_rvalue_reference(...) -> type_identity<T>;

template<typename T>
struct is_rvalue_referencable : is_not_same<type_identity<T>, decltype(try_add_rvalue_reference<T>(0))> {};

template<typename T>
struct is_referencable : bool_constant<is_rvalue_referencable<T>::value && is_lvalue_referencable<T>::value> {};
}

/**
 * add_lvalue_reference
 * @tparam T
 */
template<typename T>
struct add_lvalue_reference {
  using type = typename decltype(detail::try_add_lvalue_reference<T>(0))::type;
};
template<typename T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;



/**
 * add_rvalue_reference
 * @tparam T
 */
template<typename T>
struct add_rvalue_reference {
  using type = typename decltype(detail::try_add_rvalue_reference<T>(0))::type;
};
template<typename T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;



/**
 * remove_pointer
 * @tparam T
 */
template<typename T> struct remove_pointer                    { using type = T; };
template<typename T> struct remove_pointer<T*>                { using type = T; };
template<typename T> struct remove_pointer<const T*>          { using type = const T; };
template<typename T> struct remove_pointer<volatile T*>       { using type = volatile T; };
template<typename T> struct remove_pointer<const volatile T*> { using type = const volatile T; };
template<typename T> using remove_pointer_t = typename remove_pointer<T>::type;



namespace detail {
template<typename T>
auto pointer_test(int) -> type_identity<remove_reference_t<T>*>;

template<typename T>
auto pointer_test(...) -> type_identity<T>;
}

/**
 * add_pointer
 * @tparam T
 */
template<typename T> struct add_pointer : decltype(detail::pointer_test<T>(0)) {};
template<typename T> using add_pointer_t = typename add_pointer<T>::type;



/**
 * remove_extent
 * @tparam T
 */
template<typename T> struct remove_extent { using type = T; };
template<typename T> struct remove_extent<T[]> { using type = T; };
template<typename T, size_t N> struct remove_extent<T[N]> { using type = T; };
template<typename T> using remove_extent_t = typename remove_extent<T>::type;



/**
 * remove_all_extents
 * @tparam T
 */
template<typename T> struct remove_all_extents { using type = T; };
template<typename T> struct remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };
template<typename T, size_t N> struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };
template<typename T> using remove_all_extents_t = typename remove_all_extents<T>::type;



/**
 * is_void
 * @tparam T
 */
template<typename T> struct is_void : is_same<void, remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_void_v = is_void<T>::value;



/**
 * is_null_pointer
 * @tparam T
 */
template<typename T> struct is_null_pointer : is_same<nullptr_t, remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_null_pointer_v = is_null_pointer<T>::value;



/**
 * is_integral
 * @tparam T
 */
template<typename T> using is_integral = std::is_integral<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_integral_v = is_integral<T>::value;



namespace detail {
template<typename T> struct is_floating_point_impl    : false_type {};
template<> struct is_floating_point_impl<float>       : true_type {};
template<> struct is_floating_point_impl<double>      : true_type {};
template<> struct is_floating_point_impl<long double> : true_type {};
}
/**
 * is_floating_point
 * @tparam T
 */
template<typename T> struct is_floating_point : detail::is_floating_point_impl<remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_floating_point_v = is_floating_point<T>::value;



/**
 * is_array
 * @tparam T
 */
template<typename T> struct is_array : false_type {};
template<typename T> struct is_array<T[]> : true_type {};
template<typename T, size_t N> struct is_array<T[N]> : true_type {};
template<typename T> SS_INLINE_VAR constexpr bool is_array_v = is_array<T>::value;



/**
 * is_enum
 * @tparam T
 */
template<typename T> using is_enum = std::is_enum<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_enum_v = is_enum<T>::value;



/**
 * is_union
 * @tparam T
 */
template<typename T> using is_union = std::is_union<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_union_v = is_union<T>::value;



/**
 * is_class
 * @tparam T
 */
template<typename T> using is_class = std::is_class<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_class_v = is_class<T>::value;



namespace detail {
template<typename T> struct is_pointer : false_type {};
template<typename T> struct is_pointer<T*> : true_type {};
}
/**
 * is_pointer
 * @tparam T
 */
template<typename T> struct is_pointer : detail::is_pointer<remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_pointer_v = is_pointer<T>::value;



/**
 * is_lvalue_reference
 * @tparam T
 */
template<typename T> struct is_lvalue_reference : false_type {};
template<typename T> struct is_lvalue_reference<T&> : true_type {};
template<typename T> SS_INLINE_VAR constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;



/**
 * is_rvalue_reference
 * @tparam T
 */
template<typename T> struct is_rvalue_reference : false_type {};
template<typename T> struct is_rvalue_reference<T&&> : true_type {};
template<typename T> SS_INLINE_VAR constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;



/**
 * is_reference
 * @tparam T
 */
template<typename T> struct is_reference
  : bool_constant<is_lvalue_reference<T>::value ||
    is_rvalue_reference<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_reference_v = is_reference<T>::value;



/**
 * is_function
 * @tparam T
 */
template<typename T> struct is_function : bool_constant<!is_const<const T>::value && !is_reference<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_function_v = is_function<T>::value;



namespace detail {
template<typename T> struct is_member_pointer : false_type {};
template<typename C, typename T> struct is_member_pointer<T(C::*)> : true_type {};
}
/**
 * is_member_pointer
 * @tparam T
 */
template<typename T> struct is_member_pointer : detail::is_member_pointer<remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_member_pointer_v = is_member_pointer<T>::value;



namespace detail {
template<typename T> struct is_member_function_pointer_nocv : false_type {};
template<typename C, typename T> struct is_member_function_pointer_nocv<T(C::*)> : is_function<T> {};
}
/**
 * is_member_function_pointer
 * @tparam T
 */
template<typename T> struct is_member_function_pointer : detail::is_member_function_pointer_nocv<remove_cv_t<T>> {};
template<typename T> SS_INLINE_VAR constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;



/**
 * is_member_object_pointer
 * @tparam T
 */
template<typename T> struct is_member_object_pointer
  : bool_constant<is_member_pointer<T>::value &&
    !is_member_function_pointer<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;



/**
 * is_arithmetic
 * @tparam T
 */
template<typename T> struct is_arithmetic
  : bool_constant<is_integral<T>::value ||
    is_floating_point<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_arithmetic_v = is_arithmetic<T>::value;



/**
 * is_fundamental
 * @tparam T
 */
template<typename T> struct is_fundamental
  : bool_constant<is_arithmetic<T>::value ||
    is_void<T>::value ||
    is_null_pointer<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_fundamental_v = is_fundamental<T>::value;



/**
 * is_scalar
 * @tparam T
 */
template<typename T> struct is_scalar
  : bool_constant<is_arithmetic<T>::value ||
    is_pointer<T>::value ||
    is_member_pointer<T>::value ||
    is_enum<T>::value ||
    is_null_pointer<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_scalar_v = is_scalar<T>::value;



/**
 * is_object
 * @tparam T
 */
template<typename T> struct is_object
  : bool_constant<!is_function<T>::value &&
    !is_reference<T>::value &&
    !is_void<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_object_v = is_object<T>::value;



/**
 * is_compound
 * @tparam T
 */
template<typename T> struct is_compound
  : bool_constant<!is_fundamental<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_compound_v = is_compound<T>::value;



namespace detail {

struct unused {};

template<typename T, typename = void>
struct is_complete : false_type {};

template <typename T>
struct is_complete<T,
  enable_if_t<std::is_object<T>::value &&
              !std::is_pointer<T>::value &&
              (sizeof(T) > 0)>> : true_type {};

template<typename T, typename ...Args>
auto is_constructible_test(int) -> type_identity<decltype(T(std::declval<Args>()...))>;

template<typename T, typename ...Args>
auto is_constructible_test(...) -> unused;

template<bool v /* false */, typename T, typename ...Args>
struct is_constructible_check :
  bool_constant<is_reference<T>::value &&
                is_not_same<unused, decltype(is_constructible_test<T, Args...>(0))>::value> {};

template<typename T, typename ...Args>
struct is_constructible_check<true, T, Args...> :
  bool_constant<is_not_same<unused, decltype(is_constructible_test<T, Args...>(0))>::value>
{
  static_assert(is_complete<T>::value, "T must be complete type");
};

template<typename T, typename ...Args>
struct is_constructible_impl : is_constructible_check<is_object<T>::value, T, Args...> {};

}
/**
 * is_constructible
 * @tparam T
 * @tparam Args
 */
template<typename T, typename ...Args>
struct is_constructible : detail::is_constructible_impl<T, Args...> {};
template<typename T, typename ...Args>
SS_INLINE_VAR constexpr bool is_constructible_v = is_constructible<T, Args...>::value;



/**
 * is_trivially_constructible
 * @tparam T class type
 * @tparam Args constructor parameter types
 */
template<typename T, typename ...Args>
using is_trivially_constructible = std::is_trivially_constructible<T, Args...>;
template<typename T, typename ...Args>
SS_INLINE_VAR constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;



namespace detail {
template<bool v, typename T, typename ...Args>
struct is_nothrow_constructible_impl : false_type {};

template<typename T, typename ...Args>
struct is_nothrow_constructible_impl<true, T, Args...> : bool_constant<noexcept(T(std::declval<Args>()...))> {};
}

/**
 * is_nothrow_constructible
 * @tparam T
 * @tparam Args
 */
template<typename T, typename ...Args>
struct is_nothrow_constructible
  : detail::is_nothrow_constructible_impl<is_constructible<T, Args...>::value, T, Args...> {};
template<typename T, typename ...Args>
SS_INLINE_VAR constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;



/**
 * is_default_constructible
 * @tparam T
 */
template<typename T>
struct is_default_constructible : is_constructible<T> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_default_constructible_v = is_default_constructible<T>::value;



/**
 * is_trivially_default_constructible
 * @tparam T
 */
template<typename T>
struct is_trivially_default_constructible : is_trivially_constructible<T> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;



/**
 * is_nothrow_default_constructible
 * @tparam T
 */
template<typename T>
struct is_nothrow_default_constructible : is_nothrow_constructible<T> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;



namespace detail {
template<typename T, template<typename, typename...> class Test, bool v = is_lvalue_referencable<T>::value>
struct test_copy_ctor : false_type {};

template<typename T, template<typename, typename...> class Test>
struct test_copy_ctor<T, Test, true> : Test<T, const T&> {};
}
/**
 * is_copy_constructible
 * @tparam T
 */
template<typename T> struct is_copy_constructible : detail::test_copy_ctor<T, is_constructible> {};
template<typename T> SS_INLINE_VAR constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;



/**
 * is_trivially_copy_constructible
 * @tparam T
 */
template<typename T>
struct is_trivially_copy_constructible : detail::test_copy_ctor<T, is_trivially_constructible> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;



/**
 * is_nothrow_copy_constructible
 * @tparam T
 */
template<typename T>
struct is_nothrow_copy_constructible : detail::test_copy_ctor<T, is_nothrow_copy_constructible> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;



namespace detail {
template<typename T, template<typename, typename...> class Test, bool v = is_rvalue_referencable<T>::value>
struct test_move_ctor : false_type {};

template<typename T, template<typename, typename...> class Test>
struct test_move_ctor<T, Test, true> : Test<T, T&&> {};
}

/**
 * is_move_constructible
 * @tparam T
 */
template<typename T> struct is_move_constructible : detail::test_move_ctor<T, is_constructible> {};
template<typename T> SS_INLINE_VAR constexpr bool is_move_constructible_v = is_move_constructible<T>::value;



/**
 * is_trivially_move_constructible
 * @tparam T
 */
template<typename T>
struct is_trivially_move_constructible : detail::test_move_ctor<T, is_trivially_constructible> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;



/**
 * is_nothrow_move_constructible
 * @tparam T
 */
template<typename T>
struct is_nothrow_move_constructible : detail::test_move_ctor<T, is_nothrow_constructible> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;



namespace detail {
template<typename T, typename U>
auto is_assignable_test(int) -> type_identity<decltype(std::declval<T>() = std::declval<U>())>;

template<typename T, typename U>
auto is_assignable_test(...) -> unused;
}

/**
 * is_assignable
 * @tparam T lhs
 * @tparam U rhs
 */
template<typename T, typename U>
struct is_assignable : is_not_same<detail::unused, decltype(detail::is_assignable_test<T, U>(0))> {
  static_assert(!is_object<T>::value || detail::is_complete<T>::value, "T must be complete type");
};
template<typename T, typename U>
SS_INLINE_VAR constexpr bool is_assignable_v = is_assignable<T, U>::value;



/**
 * is_trivially_assignable
 * @tparam T
 * @tparam U
 */
template<typename T, typename U>
using is_trivially_assignable = std::is_trivially_assignable<T, U>;
template<typename T, typename U>
SS_INLINE_VAR constexpr bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;



namespace detail {
template<typename T, typename U, bool v = is_assignable<T, U>::value>
struct is_nothrow_assignable_impl : false_type {};

template<typename T, typename U>
struct is_nothrow_assignable_impl<T, U, true> : bool_constant<noexcept(std::declval<T>() = std::declval<U>())> {};
}
/**
 * is_nothrow_assignable
 * @tparam T
 * @tparam U
 */
template<typename T, typename U>
struct is_nothrow_assignable : detail::is_nothrow_assignable_impl<T, U> {};
template<typename T, typename U>
SS_INLINE_VAR constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;



namespace detail {
template<typename T, template<typename, typename...> class Test, bool v = is_lvalue_referencable<T>::value>
struct test_copy_assign : false_type {};

template<typename T, template<typename, typename...> class Test>
struct test_copy_assign<T, Test, true> : Test<T, const T&> {};
}

/**
 * is_copy_assignable
 * @tparam T
 */
template<typename T> struct is_copy_assignable : detail::test_copy_assign<T, is_assignable> {};
template<typename T> SS_INLINE_VAR constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;



/**
 * is_trivially_copy_assignable
 * @tparam T
 */
template<typename T>
struct is_trivially_copy_assignable : detail::test_copy_assign<T, is_trivially_assignable> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;



/**
 * is_nothrow_copy_assignable
 * @tparam T
 */
template<typename T>
struct is_nothrow_copy_assignable : detail::test_copy_assign<T, is_nothrow_assignable> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;



namespace detail {
template<typename T, template<typename, typename...> class Test, bool v = is_rvalue_referencable<T>::value>
struct test_move_assign : false_type {};

template<typename T, template<typename, typename...> class Test>
struct test_move_assign<T, Test, true> : Test<T, T&&> {};
}

/**
 * is_move_assignable
 * @tparam T
 */
template<typename T> struct is_move_assignable : detail::test_move_assign<T, is_assignable> {};
template<typename T> SS_INLINE_VAR constexpr bool is_move_assignable_v = is_move_assignable<T>::value;



/**
 * is_trivially_move_assignable
 * @tparam T
 */
template<typename T>
struct is_trivially_move_assignable : detail::test_move_assign<T, is_trivially_assignable> {};
template<typename T>
SS_INLINE_VAR constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;



/**
 * is_nothrow_move_assignable
 * @tparam T
 */
template<typename T>
struct is_nothrow_move_assignable : detail::test_move_assign<T, is_nothrow_assignable> {};
template<typename T> SS_INLINE_VAR constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;



namespace detail {
template<typename T, typename U = remove_all_extents_t<T>>
auto destructible_test(int) -> type_identity<decltype(std::declval<U&>().~U())>;

template<typename T>
auto destructible_test(...) -> unused;
}
/**
 * is_destructible
 * @tparam T
 */
template<typename T>
struct is_destructible
  : bool_constant<is_reference<T>::value ||
                  is_not_same<detail::unused, decltype(detail::destructible_test<T>(0))>::value> {};

template<typename T>
SS_INLINE_VAR constexpr bool is_destructible_v = is_destructible<T>::value;



/**
 * is_trivially_destructible
 * @tparam T
 */
template<typename T> using is_trivially_destructible = std::is_trivially_destructible<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;



namespace detail {
template<typename T, bool v = is_destructible<T>::value, typename U = remove_all_extents_t<T>>
struct is_nothrow_destructible_impl : bool_constant<noexcept(std::declval<U&>().~U())> {};

template<typename T>
struct is_nothrow_destructible_impl<T, false> : false_type {};
}

/**
 * is_nothrow_desetructible
 * @tparam T
 */
template<typename T> struct is_nothrow_destructible : detail::is_nothrow_destructible_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;



/**
 * has_virtual_destructor
 * @tparam T
 */
template<typename T> using has_virtual_destructor = std::has_virtual_destructor<T>;
template<typename T> SS_INLINE_VAR constexpr bool has_virtual_destructor_v = has_virtual_destructor<T>::value;



namespace detail {
namespace swap {
using std::swap;

template<typename T, typename U>
auto swappable_test(int) -> type_identity<decltype(swap(std::declval<T>(), std::declval<U>()))>;

template<typename T, typename U>
auto swappable_test(...) -> unused;

template<typename T, typename U>
struct is_swappable_with_impl
  : bool_constant<is_not_same<unused, decltype(swappable_test<T, U>(0))>::value &&
                  is_not_same<unused, decltype(swappable_test<U, T>(0))>::value> {};

template<typename T, typename U, bool v = is_swappable_with_impl<T, U>::value>
struct is_nothrow_swappable_with_impl : false_type {};

template<typename T, typename U>
struct is_nothrow_swappable_with_impl<T, U, true>
  : bool_constant<noexcept(swap(std::declval<T>(), std::declval<U>())) &&
                  noexcept(swap(std::declval<U>(), std::declval<T>()))> {};

} // namespace swap
} // namespace detail

/**
 * is_swappable_with
 * @tparam T
 * @tparam U
 */
template<typename T, typename U> struct is_swappable_with : detail::swap::is_swappable_with_impl<T, U> {};
template<typename T, typename U> SS_INLINE_VAR constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;



namespace detail {
template<typename T, bool v = is_referencable<T>::value> struct is_swappable_impl : false_type {};
template<typename T> struct is_swappable_impl<T, true> : is_swappable_with<T&, T&> {};
}

/**
 * is_swappable
 * @tparam T
 */
template<typename T> struct is_swappable : detail::is_swappable_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_swappable_v = is_swappable<T>::value;



/**
 * is_nothrow_swappable_with
 * @tparam T
 * @tparam U
 */
template<typename T, typename U>
struct is_nothrow_swappable_with : detail::swap::is_nothrow_swappable_with_impl<T, U> {};
template<typename T, typename U>
SS_INLINE_VAR constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;



namespace detail {
template<typename T, bool v = is_referencable<T>::value> struct is_nothrow_swappable_impl : false_type {};
template<typename T> struct is_nothrow_swappable_impl<T, true> : is_nothrow_swappable_with<T&, T&> {};
}

/**
 * is_nothrow_swappable
 * @tparam T
 */
template<typename T> struct is_nothrow_swappable : detail::is_nothrow_swappable_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;



/**
 * is_trivially_copyable
 * @tparam T
 */
template<typename T> using is_trivially_copyable = std::is_trivially_copyable<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;



/**
 * is_trivial
 * @tparam T
 */
template<typename T>
struct is_trivial : bool_constant<is_trivially_copyable<T>::value && is_trivially_default_constructible<T>::value> {};
template<typename T> SS_INLINE_VAR constexpr bool is_trivial_v = is_trivial<T>::value;



/**
 * is_standard_layout
 * @tparam T
 */
template<typename T> using is_standard_layout = std::is_standard_layout<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_standard_layout_v = is_standard_layout<T>::value;



/**
 * is_pod (deprecated in C++20)
 * @tparam T
 */
SS_AFTER_CXX20([[deprecated]])
template<typename T> struct is_pod : bool_constant<is_trivial<T>::value && is_standard_layout<T>::value> {};

SS_AFTER_CXX20([[deprecated]])
template<typename T> SS_INLINE_VAR constexpr bool is_pod_v = is_pod<T>::value;



# if SS_CXX_VER >= 17
/**
 * has_unique_object_representation (C++17)
 * @tparam T
 */
template<typename T> using has_unique_object_representation = std::has_unique_object_representations<T>;
template<typename T>
inline constexpr bool has_unique_object_representation_v = has_unique_object_representation<T>::value;
# endif



namespace detail {
template<typename T>
struct empty_test1 : T { SS_MAYBE_UNUSED int dummy; };
struct empty_test2     { SS_MAYBE_UNUSED int dummy; };

template<typename T, bool v = is_class<T>::value> struct is_empty_impl : false_type {};
template<typename T> struct is_empty_impl<T, true> : bool_constant<sizeof(empty_test1<T>) == sizeof(empty_test2)> {};
}

/**
 * is_empty
 * @tparam T
 */
template<typename T> struct is_empty : detail::is_empty_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_empty_v = is_empty<T>::value;



namespace detail {
//template<typename T, bool v = is_class<T>::value> struct is_polymorphic_impl : false_type {};
//template<typename T> struct is_polymorphic_impl<T, true> :
//  bool_constant<!is_empty<T>::value && sizeof(empty_test1<T>) != sizeof(T) + sizeof(empty_test2)> {};

template<typename T>
auto test_dynamic_cast(int) -> type_identity<decltype(dynamic_cast<const volatile void*>(static_cast<T*>(nullptr)))>;

template<typename T>
auto test_dynamic_cast(...) -> unused;
}

/**
 * is_polymorphic
 * @tparam T
 */
template<typename T> struct is_polymorphic : is_not_same<detail::unused, decltype(detail::test_dynamic_cast<T>(0))> {};
template<typename T> SS_INLINE_VAR constexpr bool is_polymorphic_v = is_polymorphic<T>::value;



namespace detail {
template<typename T> auto test_abstract(int) -> T;
template<typename T> auto test_abstract(...) -> unused;

template<typename T, bool v = is_class<T>::value>
struct is_abstract_impl : is_not_same<unused, decltype(test_abstract<T>(0))> {};

template<typename T>
struct is_abstract_impl<T, false> : false_type {};
}

/**
 * is_abstract
 * @tparam T
 */
template<typename T> struct is_abstract : detail::is_abstract_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_abstract_v = is_abstract<T>::value;



/**
 * is_final
 * @tparam T
 */
template<typename T> using is_final = std::is_final<T>;
template<typename T> SS_INLINE_VAR constexpr bool is_final_v = is_final<T>::value;



# if SS_CXX_VER >= 17
/**
 * is_aggregate
 * @tparam T
 */
template<typename T> using is_aggregate = std::is_aggregate<T>;
template<typename T> inline constexpr bool is_aggregate_v = is_aggregate<T>::value;
# endif



namespace detail {
template<typename T, bool v = is_arithmetic<T>::value>
struct is_signed_impl : bool_constant<(T(-1) < T(0))> {};

template<typename T>
struct is_signed_impl<T, false> : false_type {};
}

/**
 * is_signed
 * @tparam T
 */
template<typename T> struct is_signed : detail::is_signed_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_signed_v = is_signed<T>::value;



namespace detail {
template<typename T, bool v = is_arithmetic<T>::value>
struct is_unsigned_impl : bool_constant<(T(0) < T(-1))> {};

template<typename T>
struct is_unsigned_impl<T, false> : false_type {};
}

/**
 * is_unsigned
 * @tparam T
 */
template<typename T> struct is_unsigned : detail::is_unsigned_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_unsigned_v = is_unsigned<T>::value;



/**
 * is_bounded_array
 * @tparam T
 */
template<typename T> struct is_bounded_array : false_type {};
template<typename T, size_t N> struct is_bounded_array<T[N]> : true_type {};
template<typename T> SS_INLINE_VAR constexpr bool is_bounded_array_v = is_bounded_array<T>::value;



/**
 * is_unbounded_array
 * @tparam T
 */
template<typename T> struct is_unbounded_array : false_type {};
template<typename T> struct is_unbounded_array<T[]> : true_type {};
template<typename T> SS_INLINE_VAR constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;



namespace detail {
template<typename T, bool v = is_enum<T>::value>
struct is_scoped_enum_impl : is_constructible<int, T> {};

template<typename T>
struct is_scoped_enum_impl<T, false> : false_type {};
}

/**
 * is_scoped_enum
 * @tparam T
 */
template<typename T> struct is_scoped_enum : detail::is_scoped_enum_impl<T> {};
template<typename T> SS_INLINE_VAR constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;



/**
 * alignment_of
 * @tparam T
 */
template<typename T>
struct alignment_of : integral_constant<size_t, alignof(T)> {};
template<typename T> SS_INLINE_VAR constexpr bool alignment_of_v = alignment_of<T>::value;



/**
 * rank
 * @tparam T
 */
template<typename T> struct rank : integral_constant<size_t, 0> {};
template<typename T> struct rank<T[]> : integral_constant<size_t, rank<T>::value + 1> {};
template<typename T, size_t N> struct rank<T[N]> : integral_constant<size_t, rank<T>::value + 1> {};
template<typename T> SS_INLINE_VAR constexpr bool rank_v = rank<T>::value;



namespace detail {

template<typename T, unsigned N>
struct extent_impl : integral_constant<size_t, 0> {};

template<typename T>
struct extent_impl<T[], 0> : integral_constant<size_t, 0> {};

template<typename T, unsigned N>
struct extent_impl<T[], N> : extent_impl<T, N-1> {};

template<typename T, size_t K>
struct extent_impl<T[K], 0> : integral_constant<size_t, K> {};

template<typename T, size_t K, unsigned N>
struct extent_impl<T[K], N> : extent_impl<T, N-1> {};

}
/**
 * extent
 * @tparam T
 */
template<typename T, unsigned N = 0> struct extent : detail::extent_impl<T, N> {};
template<typename T, unsigned N = 0> SS_INLINE_VAR constexpr size_t extent_v = extent<T, N>::value;



/**
 * is_base_of
 * @tparam Base
 * @tparam Derived
 */
template<typename Base, typename Derived>
struct is_base_of :
  bool_constant<is_class<Base>::value &&
    is_class<Derived>::value &&
    is_assignable<Base&, Derived>::value> {};
template<typename Base, typename Derived>
SS_INLINE_VAR constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;



namespace detail {
template<typename From, typename To>
auto convertible_test(int) -> type_identity<decltype(std::declval<void(&)(To)>()(std::declval<From>()))>;

template<typename From, typename To>
auto convertible_test(...) -> unused;
}
/**
 * is_convertible
 * @tparam From
 * @tparam To
 */
template<typename From, typename To>
struct is_convertible :
  bool_constant<is_not_same<detail::unused, decltype(detail::convertible_test<From, To>(0))>::value ||
    (is_void<From>::value && is_void<To>::value)> {};
template<typename From, typename To>
SS_INLINE_VAR constexpr bool is_convertible_v = is_convertible<From, To>::value;



namespace detail {
template<typename From, typename To>
auto nothrow_convertible_test(int) -> type_identity<decltype(std::declval<void(&)(To)noexcept>()(std::declval<From>()))>;

template<typename From, typename To>
auto nothrow_convertible_test(...) -> unused;

template<typename From, typename To,
  bool v = is_not_same<unused, decltype(nothrow_convertible_test<From, To>(0))>::value>
struct is_nothrow_convertible_impl :
  bool_constant<noexcept(std::declval<void(&)(To)noexcept>()(std::declval<From>())) ||
    (is_void<From>::value && is_void<To>::value)> {};

template<typename From, typename To>
struct is_nothrow_convertible_impl<From, To, false> : false_type {};
}
/**
 * is_nothrow_convertible
 * @tparam From
 * @tparam To
 */
template<typename From, typename To>
struct is_nothrow_convertible : detail::is_nothrow_convertible_impl<From, To> {};
template<typename From, typename To>
SS_INLINE_VAR constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;


# if SS_CXX_VER >= 20
/**
 * is_layout_compatible
 * @tparam T
 * @tparam U
 */
template<typename T, typename U> using is_layout_compatible = std::is_layout_compatible<T, U>;
template<typename T, typename U> inline constexpr bool is_layout_compatible_v = is_layout_compatible<T, U>::value;



/**
 * is_pointer_interconvertible_base_of
 * @tparam Base
 * @tparam U
 */
template<typename Base, typename Derived>
struct is_pointer_interconvertible_base_of = std::is_pointer_interconvertible_base_of<Base, Derived>;
template<typename Base, typename Derived>
inline constexpr bool is_pointer_interconvertible_base_of_v = is_pointer_interconvertible_base_of<Base, Derived>::value;
# endif


// TODO
//template<typename Fn, typename ...ArgTypes>
//struct is_invocable {};



/**
 * aligned_storage
 * @tparam Len
 * @tparam Align
 */
template<size_t Len, size_t Align = alignof(std::aligned_storage_t<Len>)>
using aligned_storage = std::aligned_storage<Len, Align>;
template<size_t Len, size_t Align = alignof(std::aligned_storage_t<Len>)>
using aligned_storage_t = typename aligned_storage<Len, Align>::type;



/**
 * aligned_union
 * @tparam Len
 * @tparam Types
 */
template<size_t Len, typename ...Types>
struct aligned_union {
  SS_INLINE_VAR static constexpr size_t alignment_value = std::max({alignof(Types)...});
  struct type {
    alignas(alignment_value) char data[std::max({Len, sizeof(Types)...})];
  };
};
template<size_t Len, typename ...Types>
using aligned_union_t = typename aligned_union<Len, Types...>::type;



/**
 * remove_cvref
 * @tparam T
 */
template<typename T> struct remove_cvref { using type = remove_cv_t<remove_reference_t<T>>; };
template<typename T> using remove_cvref_t = typename remove_cvref<T>::type;



namespace detail {
template<typename T, enable_if_t<is_array<T>::value, int> = 0>
auto decay_test(int) -> type_identity<remove_extent_t<T>*>;

template<typename T, enable_if_t<is_function<T>::value, int> = 0>
auto decay_test(long) -> type_identity<add_pointer_t<T>>;

template<typename T>
auto decay_test(...) -> type_identity<remove_cvref_t<T>>;
}

/**
 * decay
 * @tparam T
 */
template<typename T> struct decay {
  using type = typename decltype(detail::decay_test<remove_reference_t<T>>(0))::type;
};
template<typename T> using decay_t = typename decay<T>::type;

namespace detail {

template<typename T, typename U> struct restore_cv                      { using type = U;                 };
template<typename T, typename U> struct restore_cv<const T, U>          { using type = add_const_t<U>;    };
template<typename T, typename U> struct restore_cv<volatile T, U>       { using type = add_volatile_t<U>; };
template<typename T, typename U> struct restore_cv<const volatile T, U> { using type = add_cv_t<U>;       };

template<typename...>
struct type_list;

template<typename T>
struct type_list<T> {
  using type = T;
  using next = unused;
};

template<typename T, typename ...Args>
struct type_list<T, Args...> {
  using type = T;
  using next = type_list<Args...>;
};

template<typename List>
struct is_list_end {
  static constexpr bool value = std::is_same<unused, typename List::next>::value;
};

using signed_list = type_list<signed char, signed short, signed int, signed long, signed long long>;
using unsigned_list = type_list<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

template<typename T, typename List, bool v = (sizeof(T) == sizeof(typename List::type) || is_list_end<List>::value)>
struct promote_impl {
  using type = typename List::type;
};

template<typename T, typename List>
struct promote_impl<T, List, false> {
  using type = typename promote_impl<T, typename List::next>::type;
};

template<typename T, typename List>
struct promote {
  using type = typename promote_impl<T, List>::type;
};

template<typename T, bool v = (is_integral<T>::value || is_enum<T>::value) && is_not_same<bool, T>::value>
struct make_signed_impl {
  static_assert(always_false<T>::value, "T must be integral(except bool) or enum type");
};

template<typename T>
struct make_signed_impl<T, true> {
  using type = typename promote<T, signed_list>::type;
  static_assert(sizeof(T) == sizeof(type), "No matching promotion for T in signed_list");
};

template<> struct make_signed_impl<signed char       , true> { using type = signed char;       };
template<> struct make_signed_impl<unsigned char     , true> { using type = signed char;       };
template<> struct make_signed_impl<signed short      , true> { using type = signed short;      };
template<> struct make_signed_impl<unsigned short    , true> { using type = signed short;      };
template<> struct make_signed_impl<signed int        , true> { using type = signed int;        };
template<> struct make_signed_impl<unsigned int      , true> { using type = signed int;        };
template<> struct make_signed_impl<signed long       , true> { using type = signed long;       };
template<> struct make_signed_impl<unsigned long     , true> { using type = signed long;       };
template<> struct make_signed_impl<signed long long  , true> { using type = signed long long;  };
template<> struct make_signed_impl<unsigned long long, true> { using type = signed long long;  };

template<typename T, bool v = (is_integral<T>::value || is_enum<T>::value) && is_not_same<bool, T>::value>
struct make_unsigned_impl {
  static_assert(always_false<T>::value, "T must be integral(except bool) or enum type");
};

template<typename T>
struct make_unsigned_impl<T, true> {
  using type = typename promote<T, unsigned_list>::type;
  static_assert(sizeof(T) == sizeof(type), "No matching promotion for T in unsigned_list");
};

template<> struct make_unsigned_impl<signed char       , true> { using type = unsigned char;       };
template<> struct make_unsigned_impl<unsigned char     , true> { using type = unsigned char;       };
template<> struct make_unsigned_impl<signed short      , true> { using type = unsigned short;      };
template<> struct make_unsigned_impl<unsigned short    , true> { using type = unsigned short;      };
template<> struct make_unsigned_impl<signed int        , true> { using type = unsigned int;        };
template<> struct make_unsigned_impl<unsigned int      , true> { using type = unsigned int;        };
template<> struct make_unsigned_impl<signed long       , true> { using type = unsigned long;       };
template<> struct make_unsigned_impl<unsigned long     , true> { using type = unsigned long;       };
template<> struct make_unsigned_impl<signed long long  , true> { using type = unsigned long long;  };
template<> struct make_unsigned_impl<unsigned long long, true> { using type = unsigned long long;  };

}
/**
 * make_signed
 * @tparam T
 */
template<typename T>
struct make_signed {
  using type = typename detail::restore_cv<T, typename detail::make_signed_impl<remove_cv_t<T>>::type>::type;
};
template<typename T> using make_signed_t = typename make_signed<T>::type;



/**
 * make_unsigned
 * @tparam T
 */
template<typename T>
struct make_unsigned {
  using type = typename detail::restore_cv<T, typename detail::make_unsigned_impl<remove_cv_t<T>>::type>::type;
};
template<typename T> using make_unsigned_t = typename make_unsigned<T>::type;



/**
 * conjunction
 * @tparam ...B
 */
template<typename ...B> struct conjunction;
template<> struct conjunction<> : true_type {};
template<typename B1> struct conjunction<B1> : B1 {};
template<typename B1, typename ...BN> struct conjunction<B1, BN...> :
  conditional_t<bool(B1::value), conjunction<BN...>, B1> {};
template<typename ...B> SS_INLINE_VAR constexpr bool conjunction_v = conjunction<B...>::value;



/**
 * disjunction
 * @tparam ...B
 */
template<typename ...B> struct disjunction;
template<> struct disjunction<> : false_type {};
template<typename B1> struct disjunction<B1> : B1 {};
template<typename B1, typename ...BN> struct disjunction<B1, BN...> :
  conditional_t<bool(B1::value), B1, disjunction<BN...>> {};
template<typename ...B> SS_INLINE_VAR constexpr bool disjunction_v = disjunction<B...>::value;



/**
 * negation
 * @tparam B
 */
template<typename B> struct negation : bool_constant<!bool(B::value)> {};
template<typename B> SS_INLINE_VAR constexpr bool negation_v = negation<B>::value;


} // namespace ss

# endif // SS_TYPE_TRAITS_H_
