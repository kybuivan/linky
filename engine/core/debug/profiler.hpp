// Copyright (c) 2023-2024 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#if defined( __clang__ ) || defined(__GNUC__)
# define TracyFunction __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
# define TracyFunction __FUNCSIG__
#endif
#include <tracy/Tracy.hpp>

#if LINKY_PROFILING
#include <tracy/public/client/TracyLock.hpp>
#endif

namespace linky::debug {

static const unsigned PROFILER_COLOR_EVENTS = 0xb26d19;
static const unsigned PROFILER_COLOR_RESOURCES = 0x006b82;

void SetProfilerThreadName(const char* name);

}

#define LINKY_PROFILE_FUNCTION()                   ZoneScopedN(__FUNCTION__)
#define LINKY_PROFILE_C(name, color)               ZoneScopedNC(name, color)
#define LINKY_PROFILE(name)                        ZoneScopedN(name)
#define LINKY_PROFILE_THREAD(name)                 linky::debug::SetProfilerThreadName(name)
#define LINKY_PROFILE_VALUE(name, value)           TracyPlot(name, value)
#define LINKY_PROFILE_FRAME()                      FrameMark
#define LINKY_PROFILE_MESSAGE(txt, len)            TracyMessage(txt, len)
#define LINKY_PROFILE_ZONENAME(txt, len)           ZoneName(txt, len)

#if LINKY_PROFILING
#   define LINKY_PROFILE_SRC_LOCATION(title)       [] () -> const tracy::SourceLocationData* { static const tracy::SourceLocationData srcloc { nullptr, title, __FILE__, __LINE__, 0 }; return &srcloc; }()
#   define LINKY_PROFILE_MUTEX(name)               ProfiledMutex name{LINKY_PROFILE_SRC_LOCATION_DATA(#name)}
#else
#   define LINKY_PROFILE_SRC_LOCATION_DATA(title)
#   define LINKY_PROFILE_MUTEX(name)               Mutex name{}
#endif