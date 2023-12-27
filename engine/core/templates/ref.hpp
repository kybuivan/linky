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
#include <memory>

namespace linky {

// template<typename T> using scope = std::unique_ptr<T>;

// template<typename T, typename ... Args>
// constexpr scope<T> create_scope(Args&& ... args)
// {
//     return std::make_unique<T>(std::forward<Args>(args)...);
// }

// template<typename T> using ref = std::shared_ptr<T>;

// template<typename T, typename ... Args>
// constexpr ref<T> create_ref(Args&& ... args)
// {
//     return std::make_shared<T>(std::forward<Args>(args)...);
// }

// template<typename T, typename ... Args>
// constexpr ref<T> cast_ref(Args&& ... args)
// {
//     return std::dynamic_pointer_cast<T>(std::forward<Args>(args)...);
// }
}
