#pragma once
#include <string>

namespace linky {
namespace core {
class image_loader {
public:
    static unsigned char* load_stb_image(const std::string& path, int& width, int& height, int& nrComponents);
};
}
}
