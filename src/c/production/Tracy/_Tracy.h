#define TRACY_ENABLE

#if defined(__clang__)
  #undef TRACY_API
  #if defined(_WIN32)
    #define TRACY_API extern __declspec(dllimport) __attribute__((visibility("default")))
  #else
    #define TRACY_API extern __attribute__((visibility("default")))
  #endif
#endif

#include "public/tracy/TracyC.h"