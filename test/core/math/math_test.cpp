#include <catch2/catch_test_macros.hpp>
#include <core/math/math.hpp>

namespace linky::core {
TEST_CASE ("math vec2") {
    glm::vec2 pos = glm::vec2(0);

    REQUIRE(pos.x == 0);
    REQUIRE(pos.y == 0);
}
}