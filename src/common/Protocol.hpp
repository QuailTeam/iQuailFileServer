#pragma once

#include <stdint.h>

#ifdef _MSC_VER
#define PACK(__Declaration__)                                                  \
  __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#elif defined(__GNUC__)
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

namespace protocol {

enum struct Command : uint32_t { None, File };

PACK(struct RawRequest {
  Command cmd;
  uint32_t extraSize;
});

PACK(struct RawResponse { Command cmd; });

} // namespace protocol