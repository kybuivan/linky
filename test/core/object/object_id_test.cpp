#include <catch2/catch_test_macros.hpp>
#include <core/object/object_id.hpp>

namespace linky::core {
TEST_CASE("object_id") {
    object_id oid1;
    object_id oid2;

    REQUIRE(oid1() != oid2());
}
}
