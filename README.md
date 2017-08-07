# About in_constexpr
An approach of detecting if inside a constexpr context in a constexpr function. 

By being able to detect if we're within a constexpr context we can choose to implement
a runtime specific algorithm while having a different algorithm for doing something at runtime. 

The approach is discussed in [this post](http://saadahmad.ca/detecting-evaluation-context-inside-constexpr-functions/)

# Features
* if (in_constexpr()) - Being able to detect if in compile time 
* smart_assert        - constexpr friendly assert
* setup_if_constexpr  - enables the if (in_constexpr()) at runtime. 

# Example code
```cpp
template <typename T>
constexpr auto some_transform(T &&v) {
  if (in_constexpr()) {
    return v + 10;
  } else {
    return v * -1;
  }
}

int main() {
  if (!setup_if_constexpr()) {
    return -1;
  }
  constexpr int a = 11;
  volatile int b  = 2;

  constexpr auto x = some_transform(a);
  auto y           = some_transform(b);

  std::cout << x << std::endl;
  std::cout << y << std::endl;
}
```
Will produce the following outputs
```
21
-2
```
