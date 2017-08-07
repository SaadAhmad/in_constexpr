cmake_minimum_required(VERSION 3.0)

project(IN_CONSTEXPR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE Release ... FORCE )
endif()

add_library(in_constexpr
  STATIC
    src/if_in_constexpr.cpp
)
set(EXPORT_HEADER_FILES
  include/in_constexpr/if_in_constexpr.hpp
  include/in_constexpr/smart_assert.hpp
)

target_include_directories(in_constexpr 
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(in_constexpr
  PROPERTIES PUBLIC_HEADER "${EXPORT_HEADER_FILES}"
)

install (
  TARGETS in_constexpr
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include/in_constexpr
)

configure_file(
  "${PROJECT_SOURCE_DIR}/InConstexprConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/InConstexprConfig.cmake"
)

install(
  FILES      "${PROJECT_BINARY_DIR}/InConstexprConfig.cmake"
  DESTINATION cmake
)

add_subdirectory(examples)

