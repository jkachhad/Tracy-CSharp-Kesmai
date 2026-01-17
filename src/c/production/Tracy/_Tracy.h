// Enable Tracy C API
#ifndef TRACY_ENABLE
#define TRACY_ENABLE 1
#endif

// Make sure TracyApi.h produces an import/export annotation on Windows.
#ifndef TRACY_IMPORTS
#define TRACY_IMPORTS 1
#endif

// Include the official header once (sets __TRACYAPI_H__ include guard).
#include "public/common/TracyApi.h"

// If c2ffi/libclang is using -fvisibility=hidden, force default visibility on clang.
#if defined(__clang__)
  #undef TRACY_API
  #if defined(_WIN32)
    #define TRACY_API extern __declspec(dllimport) __attribute__((visibility("default")))
  #else
    #define TRACY_API extern __attribute__((visibility("default")))
  #endif
#endif

// Important: stop TracyC.h from re-including TracyApi.h and overwriting TRACY_API.
#ifndef __TRACYAPI_H__
#define __TRACYAPI_H__ 1
#endif

#include "public/tracy/TracyC.h"