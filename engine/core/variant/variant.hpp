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