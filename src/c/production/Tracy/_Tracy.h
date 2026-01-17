// Force re-evaluation of TracyApi.h even if something included it earlier.
#ifdef __TRACYAPI_H__
#undef __TRACYAPI_H__
#endif

#ifndef TRACY_ENABLE
#define TRACY_ENABLE 1
#endif

// Make TRACY_API non-empty on Windows.
#ifndef TRACY_IMPORTS
#define TRACY_IMPORTS 1
#endif

#include "public/common/TracyApi.h"

// Now include TracyC.h (and also force it to re-evaluate if it was included earlier).
#ifdef __TRACYC_HPP__
#undef __TRACYC_HPP__
#endif

#include "public/tracy/TracyC.h"
