project(EXAMPLES)

include_directories(${PROJECT_SOURCE_DIR}/../include)

add_executable(factorial factorial.cpp)
target_link_libraries(factorial
  PUBLIC
    in_constexpr
)

add_executable(some_transform some_transform.cpp)
target_link_libraries(some_transform
  PUBLIC
    in_constexpr
)
