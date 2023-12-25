#include <catch2/catch_test_macros.hpp>
#include <core/variant/variant.hpp>

namespace linky::core {
TEST_CASE("variant") {
    variant var1;
    variant::type type1 = variant::type_bool;
}
}