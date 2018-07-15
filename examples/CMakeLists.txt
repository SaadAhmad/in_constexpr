project(EXAMPLES)

add_executable(factorial factorial.cpp)
target_link_libraries(factorial
  PRIVATE
    in_constexpr
)

add_executable(some_transform some_transform.cpp)
target_link_libraries(some_transform
  PRIVATE
    in_constexpr
)
