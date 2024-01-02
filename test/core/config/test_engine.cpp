#include <catch2/catch_test_macros.hpp>
#include <core/config/engine.hpp>
#include <core/version.hpp>

namespace linky::core {
TEST_CASE ("[engine] version info") {
    engine e1 = engine(); // OK
    //engine e2 = e1; // ERROR
    //engine e3(e1); // ERROR
    REQUIRE(e1.get_version() == LINKY_VERSION);
}
}