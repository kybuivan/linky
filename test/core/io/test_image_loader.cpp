#include <catch2/catch_test_macros.hpp>
#include <core/io/image_loader.hpp>

namespace linky::core {
TEST_CASE("[image loader] load stb image") {
    int width = 0;
    int height = 0;
    int component = 0;
    auto pixel = image_loader::load_stb_image("image.png", width, height, component);

    REQUIRE(width == 0);
    REQUIRE(height == 0);
    REQUIRE(component == 0);
    REQUIRE(pixel.has_value() == false);
}

}