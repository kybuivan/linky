#pragma once
#include <string_view>
#include <array>
#include <bitset>
#include <magic_enum.hpp>

namespace linky::reflection {
template <typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
[[nodiscard]] constexpr auto enum_to_string(Enum value) -> std::string_view
{
    auto str = magic_enum::enum_name(value);
    return std::string(str);
}

template <typename E>
inline auto string_to_enum(std::string name) -> E
{
    auto e = magic_enum::enum_cast<E>(name);
    if(e.has_value())
        return e;
}
}