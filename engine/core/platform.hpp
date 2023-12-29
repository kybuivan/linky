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

#include <core/typedefs.hpp>

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    #define LINKY_COMPILER_MSVC
#else
    #define LINKY_COMPILER_INTEL
#endif
#if defined(__GNUC__) && !defined(__clang__)
    #define LINKY_COMPILER_GNU
#endif
#if defined(__clang__)
    #define LINKY_COMPILER_CLANG
#endif

#if defined(_WIN32)
    #define LINKY_PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define LINKY_PLATFORM_APPLE
#elif defined(__linux__)
    #define LINKY_PLATFORM_LINUX
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #define LINKY_PLATFORM_BSD
#elif defined(__sun)
    #define LINKY_PLATFORM_SOLARIS
#else
    #error "Unknown platform"
#endif