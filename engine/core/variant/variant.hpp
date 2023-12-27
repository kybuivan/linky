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
#include <variant>
#include <functional>
#include <list>
#include <core/typedefs.hpp>
#include <core/string/string.hpp>
#include <core/variant/dictionary.hpp>
#include <core/variant/event.hpp>
#include <core/variant/callable.hpp>

namespace linky {
namespace core {
struct property_info;

class variant {
public:
    using data_type = std::variant<bool, std::int64_t, double, std::string>;

    enum type {
        type_nil,

        type_bool,
        type_int,
        type_double,
        type_string,

        type_dictionary,

        type_max,
    };
    
    variant();
    variant(const variant& var);
    
    explicit variant(int i);
    explicit variant(long i);
    explicit variant(std::uint8_t i);
    explicit variant(std::uint16_t i);
    explicit variant(std::uint32_t i);
    explicit variant(std::uint64_t i);
    explicit variant(float d);
    explicit variant(double d);
    explicit variant(const std::string& s);
    explicit variant(const char* s);
    explicit variant(const unsigned char* s);
    explicit variant(bool b);

    void get_property_list(std::list<property_info> *list) {}
private:
    data_type m_data;
    type m_type = type_nil;
};
}
}