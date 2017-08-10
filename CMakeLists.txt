cmake_minimum_required(VERSION 3.0)

project(IN_CONSTEXPR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE Release )
endif()

add_library(in_constexpr
  STATIC
    src/if_in_constexpr.cpp
)

target_include_directories(in_constexpr
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set(EXPORT_HEADER_FILES
  include/in_constexpr/if_in_constexpr.hpp
  include/in_constexpr/smart_assert.hpp
)

set_target_properties(in_constexpr
  PROPERTIES PUBLIC_HEADER
    "${EXPORT_HEADER_FILES}"
)

install (
  TARGETS in_constexpr
  EXPORT in_constexpr-targets
  DESTINATION lib/in_constexpr
  PUBLIC_HEADER DESTINATION include/in_constexpr
)

install (
  EXPORT in_constexpr-targets
  DESTINATION cmake/in_constexpr
)

install(
  FILES      "in_constexpr-config.cmake"
  DESTINATION cmake/in_constexpr
)

add_subdirectory(examples)

