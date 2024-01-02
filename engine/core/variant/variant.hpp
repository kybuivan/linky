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
#include <core/math/math.hpp>

namespace linky::core {
struct property_info;

template<typename... Ts>
struct variant_helpers {
    using variant_type = std::variant<Ts...>;

    template<typename T>
    static constexpr auto is_acceptable_v = std::disjunction_v<std::is_enum<T>, std::is_same<std::decay_t<T>, Ts>...>;
};

class variant {
public:
    using helpers = variant_helpers<
        bool,
        int, unsigned int, float, double,
        //vec2i, vec3i, vec4i,
        //vec2u, vec3u, vec4u,
        //vec2f, vec3f, vec3f,
        //mat4f, quatf,
        std::string,
        std::vector<variant>,
        std::map<variant, variant>,
        std::shared_ptr<void>
    >;

    using internal_variant_type = helpers::variant_type;

    enum type {
        type_nil,

        type_bool,
        type_int,
        type_double,
        type_string,

        type_dictionary,

        type_max,
    };
    
    variant() = default;

    variant(const variant& var) = default;
    variant(variant&& var) = default;

    template<typename T, std::enable_if_t<helpers::is_acceptable_v<T>, int> = 0>
    variant(const T& data) {
        if constexpr (std::is_enum_v<T>) {
            m_data = static_cast<int>(data);
        } else {
            m_data = data;
        }
    }

    variant& operator=(const variant&) = default;
    variant& operator=(variant&&) = default;

    template<typename T, std::enable_if_t<helpers::is_acceptable_v<T>, int> = 0>
    variant& operator=(const T& data) {
        if constexpr (std::is_enum_v<T>) {
            m_data = static_cast<int>(data);
        } else {
            m_data = data;
        }
        return *this;
    }

    template<typename T>
    variant& operator=(const std::shared_ptr<T>& data) {
        m_data = data;
        return *this;
    }

    template<typename T, std::enable_if_t<helpers::is_acceptable_v<T>, int> = 0>
    operator const T& () const {
        if constexpr (std::is_enum_v<T>) {
            return static_cast<T>(std::get<int>(m_data));
        } else {
            return std::get<T>(m_data);
        }
    }

    template<typename T>
    operator std::shared_ptr<T> () const {
        return std::static_pointer_cast<T>(std::get<std::shared_ptr<void>>(m_data));
    }

    template<typename T, std::enable_if_t<helpers::is_acceptable_v<T>, int> = 0>
    bool holds() const {
        if constexpr (std::is_enum_v<T>) {
            return std::holds_alternative<int>(m_data);
        } else {
            return std::holds_alternative<T>(m_data);
        }
    }
    
    //explicit variant(int i);
    //explicit variant(long i);
    //explicit variant(std::uint8_t i);
    //explicit variant(std::uint16_t i);
    //explicit variant(std::uint32_t i);
    //explicit variant(std::uint64_t i);
    //explicit variant(float d);
    //explicit variant(double d);
    //explicit variant(const std::string_view& s);
    //explicit variant(bool b);

    auto get_type() const -> type;
    auto get_type_name() const -> std::string_view;

    auto to_bool() const -> bool;
    auto to_int() const -> int;
    auto to_uint() const -> unsigned int;
    auto to_string() const -> std::string;
    auto to_double() const -> double;

    void set_bool(bool b);
    void set_int(int i);
    void set_double(double d);
    void set_string(std::string_view s);

    auto is_valid() const -> bool;
    auto is_null() const -> bool;
    auto is_undefined() const -> bool;

    auto can_convert_to(type t) const -> bool;
    auto convert_to(type t) const -> variant&;

    static auto type_to_name(type t) -> std::string_view;
    static auto name_to_type(std::string_view type_name) -> type;
    void get_property_list(std::list<property_info> *list) {}
private:
    internal_variant_type m_data;
    type m_type = type_nil;
};
}