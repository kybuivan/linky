#include <catch2/catch_test_macros.hpp>
#include <core/config/engine.hpp>
#include <core/version.hpp>

namespace linky::core {
TEST_CASE ("[engine] version info") {
    engine e = engine();
    //engine e1 = e;
    //engine e1(e);
    engine& e1 = engine::get();
    auto ver = e1.get_version_info();
    REQUIRE(ver.major == LINKY_MAJOR_VERSION);
    REQUIRE(ver.minor == LINKY_MINOR_VERSION);
    REQUIRE(ver.patch == LINKY_PATCH_VERSION);
    REQUIRE(ver.commit == LINKY_COMMIT_HASH);
}
}