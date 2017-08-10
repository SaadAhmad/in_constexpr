get_filename_component(
  SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH
)

include(${SELF_DIR}/in_constexpr-targets.cmake)

get_filename_component(
  in_constexpr_INCLUDE_DIRS "${SELF_DIR}/include/in_constexpr" ABSOLUTE
)
get_filename_component(
  in_constexpr_LIB_DIRS "${SELF_DIR}/lib/in_constexpr" ABSOLUTE
)