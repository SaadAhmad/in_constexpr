//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstdint>

#if defined(__GNUC__) && !defined(__clang__)
#define no_opt optimize("O0")
#elif defined(__clang__)
#define no_opt optnone
#else
#warning "in_constexpr not tested/supported on different compilers"
#define no_opt
#endif

namespace in_constexpr {

#if defined(CUSTOM_IS_CONSTEXPR_FLAG)
constexpr uint32_t IS_CONSTEXPR_FLAG = CUSTOM_IS_CONSTEXPR_FLAG;
#else
constexpr uint32_t IS_CONSTEXPR_FLAG = 0x5EEEEEFF;
#endif

template <typename T>
__attribute__((no_opt)) constexpr auto in_constexpr_impl(T) {
  return IS_CONSTEXPR_FLAG;
}

#define IN_CONSTEXPR_CAT(x, y) x##y
#define IN_CONSTEXPR_CAT2(x, y) IN_CONSTEXPR_CAT(x, y)
#if __cplusplus >= 201703L
// A nicer C++17 approach
#define in_constexpr()                                                      \
  int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0;                            \
  __builtin_expect(                                                         \
    in_constexpr::in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), \
    0)
#define in_runtime()                                                         \
  int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0;                             \
  __builtin_expect(                                                          \
    !in_constexpr::in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), \
    1)
#else
// A C++14 approach
#define in_constexpr()  bool IN_CONSTEXPR_CAT2(canary, __LINE__) = true) { \
    (void)IN_CONSTEXPR_CAT2(canary, __LINE__);                             \
  }                                                                        \
  int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0;                           \
  if ( __builtin_expect(in_constexpr::in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), 0)

#define in_runtime() bool IN_CONSTEXPR_CAT2(canary, __LINE__) = true) { \
    (void)IN_CONSTEXPR_CAT2(canary, __LINE__);                          \
  }                                                                     \
  int IN_CONSTEXPR_CAT2(__unused, __LINE__) = 0;                        \
  if ( __builtin_expect(!in_constexpr::in_constexpr_impl(IN_CONSTEXPR_CAT2(__unused, __LINE__)), 1)
#endif

bool initialize();

// This should return the second branch if the library is enabled.
inline bool is_setup() {
  if (in_constexpr()) {
    return false;
  } else {
    return true;
  }
}

namespace internal {
// We add the constructor attribute at 101 so that this will get called at
// program init time.
__attribute__((constructor(101))) inline void setup_at_init_time() {
  if (!in_constexpr::initialize()) {
    throw("Something went wrong initializing in_constexpr()");
  }
}

} // namespace internal

} // namespace in_constexpr
