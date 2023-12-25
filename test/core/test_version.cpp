#include <catch2/catch_test_macros.hpp>
#include <core/version.hpp>
#include <format>

TEST_CASE("version") {
    auto ver = std::format("{}.{}.{}", LINKY_MAJOR_VERSION, LINKY_MINOR_VERSION, LINKY_PATCH_VERSION);
    REQUIRE(LINKY_VERSION == ver);
}