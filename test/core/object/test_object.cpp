#include <catch2/catch_test_macros.hpp>
#include <core/object/object.hpp>

namespace linky::core {
TEST_CASE("object") {
    object obj1;
    object obj2;
    obj1.set_parrent(&obj2);
    REQUIRE(&obj2 == obj1.get_parrent());
}
}
