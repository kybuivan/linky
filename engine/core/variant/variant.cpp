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
variant::variant()
{
    m_type = type_nil;
}

variant::variant(int i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(long i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint8_t i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint16_t i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint32_t i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint64_t i) {
    m_type = type_int;
    m_data = static_cast<std::int64_t>(i);
}

variant::variant(float d) {
    m_type = type_double;
    m_data = static_cast<double>(d);
}

variant::variant(double d) {
    m_type = type_double;
    m_data = static_cast<double>(d);
}

variant::variant(const std::string_view &s) {
    m_type = type_string;
    m_data = static_cast<std::string>(s);
}

variant::variant(const char *s) {
    m_type = type_string;
    m_data = std::string(s);
}

variant::variant(const unsigned char *s) {
    m_type = type_string;
    m_data = std::string(reinterpret_cast<const char*>(s));
}

variant::variant(bool b) {
    m_type = type_bool;
    m_data = static_cast<bool>(b);
}

auto variant::get_type() const -> type {
    return m_type;
}

auto variant::get_type_name() const -> std::string_view {
    return type_to_name(m_type);
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