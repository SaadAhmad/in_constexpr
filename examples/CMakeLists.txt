project(EXAMPLES)

include ("${PROJECT_BINARY_DIR}/../InConstexprConfig.cmake")

add_executable(factorial factorial.cpp)
target_include_directories(factorial
  PRIVATE
    ${in_constexpr_INCLUDE_DIRS}
)
target_link_libraries(factorial
  PUBLIC
    ${in_constexpr_LIBRARIES}
)

add_executable(some_transform some_transform.cpp)
target_include_directories(some_transform
  PRIVATE
    ${in_constexpr_INCLUDE_DIRS}
)
target_link_libraries(some_transform
  PUBLIC
    ${in_constexpr_LIBRARIES}
)
