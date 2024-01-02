#include <catch2/catch_test_macros.hpp>
#include <core/config/engine.hpp>
#include <core/version.hpp>

namespace linky::core {
TEST_CASE ("[engine] version info") {
    engine e = engine();
    //engine e1 = e;
    //engine e1(e);
    engine& e1 = engine::get();
    REQUIRE(e1.get_version() == LINKY_VERSION);
}
}