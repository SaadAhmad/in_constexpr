//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <in_constexpr/if_in_constexpr.hpp>
#include <in_constexpr/smart_assert.hpp>

const int N_MAX = 30;
int factorial_cache[N_MAX] = {0};

constexpr int factorial(int n){  
  smart_assert(n >= 0 && n < N_MAX, "N >= 0 && N <= N_MAX");

  if ( n == 0 ) return 1;
  else {
    if ( in_constexpr() ) { 
      return n * factorial(n-1);
    }
    else {
      std::cout << "Calling factorial " << n << std::endl;
      // Since we're in runtime, we can cache results.
      if ( factorial_cache[n] == 0 ) {
        factorial_cache[n] = n * factorial(n-1);
      }
      return factorial_cache[n];
    }
  }
}


int main() {
  if ( !setup_if_constexpr() )
  {
    return -1;
  }
  volatile int a = 5;
  volatile int b = 6;
  std::cout << factorial(a) << std::endl;
  std::cout << factorial(b) << std::endl;

  constexpr int c = factorial(3);
  // Compiler error!
  // constexpr int d = factorial(-5);

  std::cout << c << std::endl;
  // std::cout << factorial(d) << std::endl;
  return 0;
}
