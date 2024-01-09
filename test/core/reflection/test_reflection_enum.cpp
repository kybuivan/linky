#include <catch2/catch_test_macros.hpp>
#include <core/reflection/reflection_enum.hpp>

enum class Num : int32_t
{
    ONE,
    TWO,
    THREE
};

TEST_CASE("[reflection] reflection enum") {
    REQUIRE(linky::reflection::enum_to_string(Num::ONE) == "ONE");
    REQUIRE(linky::reflection::enum_to_string(Num::TWO) == "TWO");
    REQUIRE(linky::reflection::enum_to_string(Num::THREE) == "THREE");
}