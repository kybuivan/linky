#pragma once
#include <core/string/string.hpp>

namespace linky {
namespace core {
class image_loader {
public:
    static unsigned char* load_stb_image(const std::string& path, int& width, int& height, int& nrComponents);
};
}
}
