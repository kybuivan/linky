#include <catch2/catch_test_macros.hpp>
#include <core/string/string.hpp>

namespace linky::core {
TEST_CASE("string") {
    std::string str1 = "str1";
    std::string_view str2 = "str2";
    std::wstring str3 = L"str3";
    std::wstring_view str4 = L"str4";
}
}