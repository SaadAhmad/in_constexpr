cmake_minimum_required(VERSION 3.1)

project(IN_CONSTEXPR)

###############################################
# Find C++ version                            #
###############################################

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
check_cxx_compiler_flag("-std=c++1z" COMPILER_SUPPORTS_CXX17)
check_cxx_compiler_flag(foobar COMPILER_SUPPORTS_CXX17)

if("${COMPILER_SUPPORTS_CXX17}")
  set(CXX_STANDARD_TO_USE cxx_std_17)
elseif("${COMPILER_SUPPORTS_CXX14}")
  set(CXX_STANDARD_TO_USE cxx_std_14)
else()
  error("Dont have a supported compiler")
endif()

if( NOT CMAKE_BUILD_TYPE )
  # Set to release if not default set.
  set( CMAKE_BUILD_TYPE Release )
endif()

###############################################
# Create Library                              #
###############################################

add_library(in_constexpr
  STATIC
    src/if_in_constexpr.cpp
)

target_compile_features(in_constexpr
  PUBLIC
    ${CXX_STANDARD_TO_USE}
)

target_include_directories(in_constexpr
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

###############################################
# Setup installation                          #
###############################################

set(EXPORT_HEADER_FILES
  include/in_constexpr/if_in_constexpr.hpp
  include/in_constexpr/smart_assert.hpp
)

set_target_properties(in_constexpr
  PROPERTIES
    PUBLIC_HEADER "${EXPORT_HEADER_FILES}"
)

install (
  TARGETS in_constexpr
  EXPORT  in_constexpr-targets
  LIBRARY DESTINATION lib/in_constexpr
  ARCHIVE DESTINATION lib/in_constexpr
  PUBLIC_HEADER DESTINATION include/in_constexpr
)

install (
  EXPORT in_constexpr-targets
  FILE   in_constexpr-config.cmake
  NAMESPACE in_constexpr::
  DESTINATION cmake/in_constexpr
)

###############################################
# Build Examples                              #
###############################################

# Build only if no-one is including us.
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  add_subdirectory(examples)
endif()
