//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cassert>

#include <in_constexpr/if_in_constexpr.hpp>

template <int LINE>
struct assert_line {};
template <typename... Args>
constexpr inline bool assertion_failed(Args... args) {
  return true;
}

#define smart_assert(expr, message)                    \
  if (in_constexpr()) {                                \
    if (!(expr)) {                                     \
      throw assertion_failed(assert_line<__LINE__>()); \
    }                                                  \
  } else {                                             \
    assert((expr) && message);                         \
  }
