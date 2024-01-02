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

#include "variant.hpp"
#include <magic_enum.hpp>

namespace linky::core {
auto variant::get_type() const -> type
{
    return m_type;
}

auto variant::get_type_name() const -> std::string_view
{
    return type_to_name(m_type);
}

auto variant::can_convert_to(type t) const -> bool
{
    return true;
}

auto variant::type_to_name(type t) -> std::string_view
{
    return magic_enum::enum_name(t);
}

auto variant::name_to_type(std::string_view type_name) -> type
{
    auto t = magic_enum::enum_cast<type>(type_name);
    if (t.has_value()) {
        return t.value();
    }
    else {
        return type::type_nil;
    }
}
} //namespace linky::core