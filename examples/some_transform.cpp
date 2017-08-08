//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <in_constexpr/if_in_constexpr.hpp>

template <typename T>
constexpr auto some_transform(T &&v) {
  if (in_constexpr()) {
    return v + 10;
  } else {
    return v * -1;
  }
}

// This is noinline just for making the assembly easier to read
__attribute((noinline)) void print(int a) {
  std::cout << a << std::endl;
}

int main() {
  constexpr int a = 11;
  volatile int b  = 2;

  constexpr auto x = some_transform(a);
  auto y           = some_transform(b);

  print(x);
  print(y);
}
