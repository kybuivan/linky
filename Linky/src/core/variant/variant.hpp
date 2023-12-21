#pragma once
#include <string>
#include <variant>
#include <functional>
#include "core/typedefs.hpp"

namespace linky {
namespace core {
class variant {
public:
    using DataType = std::variant<bool, std::int64_t, double, std::string>;

    enum Type {
        NIL,

        BOOL,
        INT,
        DOUBLE,
        STRING,

        variant_MAX
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

private:
    DataType data;
    Type type = NIL;
};
}
}