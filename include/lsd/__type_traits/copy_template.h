//
// Created by YongGyu Lee on 5/16/24.
//

#ifndef LSD_TYPE_TRAITS_COPY_TEMPLATE_HPP_
#define LSD_TYPE_TRAITS_COPY_TEMPLATE_HPP_

#include "lsd/__type_traits/type_identity.h"

namespace lsd {

template<typename From, template<typename...> class To, template<typename, typename...> class Proj = type_identity_t>
struct copy_template;

template<template<typename...> class From, typename... T, template<typename...> class To, template<typename, typename...> class Proj>
struct copy_template<From<T...>, To, Proj> {
  using type = To<Proj<T>...>;
};

template<typename From, template<typename...> class To, template<typename, typename...> class Proj = type_identity_t>
using copy_template_t = typename copy_template<From, To, Proj>::type;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_COPY_TEMPLATE_HPP_
