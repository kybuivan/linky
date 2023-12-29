#include <catch2/catch_test_macros.hpp>
#include <core/io/image.hpp>

namespace linky::core {
TEST_CASE ("[image] create") {
    image img1 = image();

    REQUIRE(img1.get_data().empty() == true);
}
}