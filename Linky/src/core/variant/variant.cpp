#include "variant.hpp"

namespace linky {
namespace core {

variant::variant(int i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(long i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint8_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint16_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint32_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(std::uint64_t i) {
    type = INT;
    data = static_cast<std::int64_t>(i);
}

variant::variant(float d) {
    type = DOUBLE;
    data = static_cast<double>(d);
}

variant::variant(double d) {
    type = DOUBLE;
    data = static_cast<double>(d);
}

variant::variant(const std::string &s) {
    type = STRING;
    data = static_cast<std::string>(s);
}

variant::variant(const char *s) {
    type = STRING;
    data = std::string(s);
}

variant::variant(const unsigned char *s) {
    type = STRING;
    data = std::string(reinterpret_cast<const char*>(s));
}

variant::variant(bool b) {
    type = BOOL;
    data = static_cast<bool>(b);
}
} //namespace core
} //namespace linky