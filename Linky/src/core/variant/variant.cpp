#include "variant.hpp"

namespace linky {
namespace core {

variant::variant(int i) {
    m_type = type_nil;
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

variant::variant(const std::string &s) {
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
} //namespace core
} //namespace linky