#pragma once
#include <string>

namespace Linky {
class Image {
public:
    static unsigned char* load_stb_image(const std::string& path, int& width, int& height, int& nrComponents);
};
}
