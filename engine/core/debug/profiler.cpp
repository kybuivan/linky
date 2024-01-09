#include <stdint.h>

#include "profiler.hpp"
#if LINKY_PROFILING
#include "tracy/public/TracyClient.cpp"
#if _WIN32
#   include <windows.h>
#else
#   include "pthread.h"
#endif
#endif

namespace linky::debug {
void SetProfilerThreadName(const char* name)
{
#if LINKY_PROFILING
    tracy::SetThreadName(name);
#endif
}
}