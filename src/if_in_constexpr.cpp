//          Copyright Saad Ahmad 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <in_constexpr/if_in_constexpr.hpp>

#if defined (__linux__) || defined (__unix__)

#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

bool setup_if_constexpr()
{
  volatile auto temp_flag = IS_CONSTEXPR_FLAG;
  unsigned char *code = (unsigned char *)&in_constexpr_impl<int>;
  extern unsigned char etext;

  const int size = &etext - code;
  for ( int i = 0; i < size; i++ )
  {
    unsigned int &code_as_int = *(unsigned int*)(code + i);
    // Replace the constexpr flag so in_const_expr returns 0 instead of the flag.
    if ( code_as_int == temp_flag )
    {
      // Find the page the code is in
      const int page_size = getpagesize();
      auto page_addr = &code[i];
      page_addr -= (unsigned long)page_addr %  page_size;

      // We first need to unlock the page the code is in to be able to write
      {
        auto ret_unlock = mprotect(page_addr, sizeof(decltype(temp_flag)), PROT_READ | PROT_WRITE | PROT_EXEC);
        if ( ret_unlock != 0 )
        {
          return false;
        }
        // Also since we're modfying this page, we need to make sure this page 
        // does not get paged out. 
        auto ret_lock = mlock(page_addr, page_size);
        if ( ret_lock != 0 )
        {
          return false;
        }
      }
      // Set the flag to zero.
      code_as_int = 0x0;

      // Now we're done. So lock the page again
      {
        auto ret_lock = mprotect(page_addr, sizeof(decltype(temp_flag)), PROT_READ| PROT_EXEC);
        if ( ret_lock != 0 )
        {
          return false;
        }
      }
    }
  }
  return true;
}
#else
bool setup_if_constexpr()
{
  return false;
}
#endif