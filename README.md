# About in_constexpr
An approach of detecting if inside a constexpr context in a constexpr function. 

By being able to detect if we're within a constexpr context we can choose to implement
a runtime specific algorithm while having a different algorithm for doing something at runtime. 

The approach is discussed in [this post](http://saadahmad.ca/detecting-evaluation-context-inside-constexpr-functions/)

# Features
* if (in_constexpr()/in_runtime()) - Being able to detect if in runtime or compile time 
* smart_assert                     - constexpr friendly assert

# Constraints
* Only tested on GCC 5+ and Clang 3.8+
* x86 only so far
* Runtime approach only works on linux (replacing code in the binary should work under windows for now)
* See detailed descriptions about caveats [here](http://saadahmad.ca/detecting-evaluation-context-inside-constexpr-functions/#caveats)
* The library must be statically linked
* The initialization logic relies on being able to modify the .text segment of your program

# Using the library
## Building and installing
You can compile and install this library using cmake. You will need to link this library in as a static library.
You can customize and install the library using the following:
```
cmake <code directory> -DCMAKE_INSTALL_PREFIX=<install directory> && make -j && make install
```
Then just link in as you would a normal library. You can try the examples in examples/ to see how to use the library.
## Using the API and an example

To test if this library is working, you can call ```in_constexpr::is_setup()``` to see if it is working. The library should automatically call the setup by means of the constructor 
attribute and so you shouldn't need to explicitly call ```in_constexpr::initialize()``` but if it's not happening automatically, you can call that function. 

The library provides an ``` in_constexpr()``` and ```in_runtime()``` macro/method that returns if a constexpr function is within which context. This can be used to provide different code paths in each case. 
Note, you can't do something like ```if (!in_constexpr()) ``` due to those methods being a syntatic sugar. Use either ```if (in_constexpr())``` or ```if (in_runtime())```.

The library also provides a smart_assert which you can use regular assert but stil work within constexpr functions. 

You can find more examples under the examples folder. 

```cpp

const int N_MAX            = 30;
int factorial_cache[N_MAX] = {0};

constexpr int factorial(int n) {
  smart_assert(n >= 0 && n < N_MAX, "N >= 0 && N <= N_MAX");

  if (n == 0)
    return 1;
  else {
    if (in_constexpr()) {
      return n * factorial(n - 1);
    } else {
      std::cout << "Calling factorial " << n << std::endl;
      // Since we're in runtime, we can cache results.
      if (factorial_cache[n] == 0) {
        factorial_cache[n] = n * factorial(n - 1);
      }
      return factorial_cache[n];
    }
  }
}

int main() {
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
```
Will produce the following outputs
```
Calling factorial 5
Calling factorial 4
Calling factorial 3
Calling factorial 2
Calling factorial 1
120
Calling factorial 6
Calling factorial 5
720
6
```
