#ifndef SOUP_H
#define SOUP_H

#include <cstdint>
#include <vector>

namespace SIMDCPU
{
  using Word = std::uint32_t;
  constexpr Word soupSize = 1<<20; // needs to be a power of 2
  constexpr Word soupMask= soupSize-1;
  
  extern std::vector<Word> soup;
}

#include "soup.cd"
#endif
