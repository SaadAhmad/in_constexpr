//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <in_constexpr/if_in_constexpr.hpp>
#if defined(__linux__) || defined(__unix__)

#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

extern unsigned char etext;

namespace in_constexpr {

/*
 To do this, we need to
  1. Find the flag in the .text section of the program,
  2. Unlock the page the code is in it for writing,
  3. Keep the page from being unloaded
  4. Modify the FLAG to 0
  5. Lock the page again for writing
*/
bool initialize() {
  volatile auto temp_flag = IS_CONSTEXPR_FLAG;
  // If the flag is zero then that means that the binary has already been
  // modified. Consider it a success and return early.
  if (temp_flag == 0) {
    return true;
  }
  unsigned char *code = (unsigned char *)&in_constexpr_impl<int>;

  const int size = &etext - code;
  for (int i = 0; i < size; i++) {
    unsigned int &code_as_int = *(unsigned int *)(code + i);
    // Replace the constexpr flag so in_const_expr returns 0 instead of the flag.
    if (code_as_int == temp_flag) {
      // Find the page the code is in
      const int page_size = getpagesize();
      auto page_addr      = &code[i];
      page_addr -= (unsigned long)page_addr % page_size;

      // We first need to unlock the page the code is in to be able to write
      {
        auto ret_unlock = mprotect(page_addr, sizeof(decltype(temp_flag)), PROT_READ | PROT_WRITE | PROT_EXEC);
        if (ret_unlock != 0) {
          return false;
        }
        // Also since we're modfying this page, we need to make sure this page
        // does not get paged out.
        auto ret_lock = mlock(page_addr, page_size);
        if (ret_lock != 0) {
          return false;
        }
      }

      // Set the flag to zero.
      code_as_int = 0x0;

      // Now we're done. So lock the page again
      {
        auto ret_lock = mprotect(page_addr, sizeof(decltype(temp_flag)), PROT_READ | PROT_EXEC);
        if (ret_lock != 0) {
          return false;
        }
      }
      return is_setup();
    }
  }
  return false;
}
} // namespace in_constexpr
// namespace in_constexpr
#else

namespace in_constexpr {

bool initialize() {
  if (!is_setup()) {
    throw("The library was not able to be setup!"
          " This case needs to be handled by search-and-replaced");
  }
  return false;
}

} // namespace in_constexpr

#endif
