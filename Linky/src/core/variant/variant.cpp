#include "core/variant/variant.hpp"
#include "variant.hpp"

namespace Linky {

Variant::Variant(int i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(long i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(std::uint8_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(std::uint16_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(std::uint32_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(std::uint64_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

Variant::Variant(float d) {
    type = DOUBLE;
    data = static_cast<double>(d);
}

Variant::Variant(double d) {
    type = DOUBLE;
    data = static_cast<double>(d);
}

Variant::Variant(const std::string &s) {
    type = STRING;
    data = static_cast<std::string>(s);
}

Variant::Variant(const char *s) {
    type = STRING;
    data = std::string(s);
}

Variant::Variant(const unsigned char *s) {
    type = STRING;
    data = std::string(reinterpret_cast<const char*>(s));
}

Variant::Variant(bool b) {
    type = BOOL;
    data = static_cast<bool>(b);
}
} //namespace Linky