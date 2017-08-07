# About in_constexpr
An approach of detecting if inside a constexpr context in a constexpr function. 

By being able to detect if we're within a constexpr context we can choose to implement
a runtime specific algorithm while having a different algorithm for doing something at runtime. 

The approach is discussed in [this post](http://saadahmad.ca/detecting-evaluation-context-inside-constexpr-functions/)

An example of the use case is seen in the factorial example under examples,

# Features
* if (in_constexpr()) - Being able to detect if in compile time 
* smart_assert        - a constexpr friendly assert


# Example code
```cpp
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
```
