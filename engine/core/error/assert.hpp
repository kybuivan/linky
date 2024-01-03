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
#include <gsl/assert> // for Ensures, Expects
#include <format>

#if defined(LINKY_ENABLE_ASSERT)

#define LINKY_ABORT() std::abort()

#define LINKY_DO_ASSERT(file, line, expr, msg, ...)
  
#define LINKY_ASSERT(expr, msg, ...)                                              \
  LINKY_DO_ASSERT(__FILE__, __LINE__, expr, msg, ##__VA_ARGS__)

#define LINKY_DO_FAIL(file, line, msg, ...)

#define LINKY_FAIL(msg, ...) LINKY_DO_FAIL(__FILE__, __LINE__, msg, ##__VA_ARGS__)

#else

#define LINKY_DO_ASSERT(file, line, expr, msg) (void)0
#define LINKY_ASSERT(expr, msg)                (void)0
#define LINKY_DO_FAIL(file, line, msg)         (void)0
#define LINKY_FAIL(msg)                        (void)0

#endif