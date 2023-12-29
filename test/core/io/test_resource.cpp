#include <catch2/catch_test_macros.hpp>
#include <core/io/resource.hpp>

namespace linky::core {
TEST_CASE("[resource] create") {
    resource res = resource();
    REQUIRE(res.get_path() == "" );
}
}