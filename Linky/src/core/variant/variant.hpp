#pragma once
#include <string>
#include <variant>
#include "core/typedefs.hpp"

namespace Linky {
class Variant {
public:
    using DataType = std::variant<bool, std::int64_t, double, std::string>;

    enum Type {
        NIL,

        BOOL,
        INT,
        DOUBLE,
        STRING,

        VARIANT_MAX
    };
    
    Variant();
    Variant(const Variant& var);
    
    explicit Variant(int i);
    explicit Variant(long i);
    explicit Variant(std::uint8_t i);
    explicit Variant(std::uint16_t i);
    explicit Variant(std::uint32_t i);
    explicit Variant(std::uint64_t i);
    explicit Variant(float d);
    explicit Variant(double d);
    explicit Variant(const std::string& s);
    explicit Variant(const char* s);
    explicit Variant(const unsigned char* s);
    explicit Variant(bool b);

private:
    DataType data;
    Type type = NIL;
};
}