#include <catch2/catch_test_macros.hpp>
#include <core/config/engine.hpp>
#include <core/version.hpp>

namespace linky::core {
TEST_CASE ("[engine] version info") {
    engine e;
    auto ver = e.get_version_info();
    REQUIRE(ver.m_major == LINKY_MAJOR_VERSION);
    REQUIRE(ver.m_minor == LINKY_MINOR_VERSION);
    REQUIRE(ver.m_patch == LINKY_PATCH_VERSION);
    REQUIRE(ver.m_commit == LINKY_COMMIT_HASH);
}
}