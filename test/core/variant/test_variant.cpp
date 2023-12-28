#include <catch2/catch_test_macros.hpp>
#include <core/variant/variant.hpp>

namespace linky::core {
TEST_CASE("[variant] type") {
    variant var1;
    variant::type type1 = variant::type_bool;
    REQUIRE(variant::name_to_type("type_bool") == variant::type_bool);
    REQUIRE(variant::name_to_type("abc") == variant::type_nil);
    REQUIRE(variant::type_to_name(variant::type_nil) == "type_nil");
    REQUIRE(variant::type_to_name(variant::type_bool) == "type_bool");
    REQUIRE(variant::type_to_name(variant::type_max) == "type_max");
    REQUIRE(var1.get_type() == variant::type_nil);
    REQUIRE(var1.get_type_name() == "type_nil");
}
}