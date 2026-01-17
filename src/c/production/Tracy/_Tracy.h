// 1) Force Tracy on for the extract translation unit.
#ifndef TRACY_ENABLE
#define TRACY_ENABLE 1
#endif

// 2) On Windows, TracyApi.h makes TRACY_API empty unless IMPORTS/EXPORTS is defined.
#if defined(_WIN32) && !defined(TRACY_IMPORTS) && !defined(TRACY_EXPORTS)
#define TRACY_IMPORTS 1
#endif

// 3) If TracyC.h was included earlier *without* TRACY_ENABLE (can happen if something
//    pulls it in first), its include guard will lock you into the "disabled" branch.
//    Force a clean include.
#ifdef __TRACYC_HPP__
#undef __TRACYC_HPP__
#endif

// 4) Include the official TRACY_API definition once.
#include "public/common/TracyApi.h"

// 5) c2ffi uses -fvisibility=hidden; ensure clang sees default visibility.
//    Also prevent TracyC.h from re-including TracyApi.h and overwriting TRACY_API.
#if defined(__clang__)
  #undef TRACY_API
  #if defined(_WIN32)
    #if defined(TRACY_EXPORTS)
      #define TRACY_API __declspec(dllexport) __attribute__((visibility("default")))
    #else
      #define TRACY_API __declspec(dllimport) __attribute__((visibility("default")))
    #endif
  #else
    #define TRACY_API __attribute__((visibility("default")))
  #endif
#endif

#ifndef __TRACYAPI_H__
#define __TRACYAPI_H__ 1
#endif

#include "public/tracy/TracyC.h"
