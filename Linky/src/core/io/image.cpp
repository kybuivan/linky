#include "core/io/image.hpp"
#include <filesystem>
#include <stb_image.h>

namespace Linky {

unsigned char* Image::load_stb_image(const std::string& path, int& width, int& height, int& nrComponents)
{
    const auto filePath = std::filesystem::path(path);

    if (!exists(filePath)) return nullptr;

    auto pixels = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    
    return pixels;
}

}
