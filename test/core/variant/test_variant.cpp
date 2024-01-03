#include <catch2/catch_test_macros.hpp>
#include <core/variant/variant.hpp>

namespace linky::core {
TEST_CASE("[variant] type") {
    variant var_bool(true);
    //REQUIRE(true == var_bool);

    variant var_int(4);
    variant var_float(0.4f);
    variant var_double(1.4);
    variant var_string(std::string("test"));
    variant::type type1 = variant::type::e_bool;
    REQUIRE(variant::name_to_type("e_bool") == variant::type::e_bool);
    REQUIRE(variant::name_to_type("abc") == variant::type::e_nil);
    REQUIRE(variant::type_to_name(variant::type::e_nil) == "e_nil");
    REQUIRE(variant::type_to_name(variant::type::e_bool) == "e_bool");
    REQUIRE(variant::type_to_name(variant::type::e_max) == "e_max");
    //REQUIRE(var1.get_type() == variant::type::e_nil);
    //REQUIRE(var1.get_type_name() == "e_nil");
}
}