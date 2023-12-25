#include <catch2/catch_test_macros.hpp>
#include <core/config/project_setting.hpp>

namespace linky::core {
TEST_CASE("project setting config")
{
    project_config config;
    config.width = 500;
    config.height = 500;
    config.name = "config";
    config.fullscreen = false;

    REQUIRE(config.width == 500);
    REQUIRE(config.height == 500);
    REQUIRE(config.name == "config");
    REQUIRE(config.fullscreen == false);
}
}