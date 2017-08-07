//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstdint>

#if defined (__GNUC__) && !defined(__clang__)
  #define no_opt optimize("O0")
#elif defined (__clang__)
  #define no_opt optnone
#else
  #warning "in_constexpr not tested/supported on different compilers"
  #define no_opt 
#endif

#if defined (CUSTOM_IS_CONSTEXPR_FLAG)
constexpr uint32_t IS_CONSTEXPR_FLAG = CUSTOM_IS_CONSTEXPR_FLAG;
#else
constexpr uint32_t IS_CONSTEXPR_FLAG = 0x5EEEEEFF;
#endif

template<typename T>
__attribute__((no_opt))
constexpr auto in_constexpr_impl(T) {
  return IS_CONSTEXPR_FLAG;
}

#define IN_CONSTEXPR_CAT(x, y) x##y
#define IN_CONSTEXPR_CAT2(x, y) IN_CONSTEXPR_CAT(x,y)
#if 0
// A nicer C++17 approach
#define in_constexpr() \
  int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0; \
  __builtin_expect(in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), 0)
#else
// A C++14 approach
#define in_constexpr() true) {}\
   int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0; \
   if ( __builtin_expect(in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), 0)
#endif


bool setup_if_constexpr();
