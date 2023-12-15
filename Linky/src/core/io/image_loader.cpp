#include "core/io/image_loader.hpp"
#include <filesystem>
#include <stb_image.h>

namespace Linky {
namespace fs = std::filesystem;

unsigned char* ImageLoader::load_stb_image(const std::string& path, int& width, int& height, int& nrComponents) {
    
    const auto filePath = fs::path(path);

    if (!fs::exists(filePath)) return nullptr;

    auto pixels = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    
    return pixels;
}

}
