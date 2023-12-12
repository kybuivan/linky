#include "core/io/image.hpp"
#include <stb_image.h>

namespace Linky {
Image::Image(int _width, int _height, bool _mipmaps, int _format, const std::vector<uint8_t> &_data)
    : width(_width)
    , height(_height)
    , mipmaps(_mipmaps)
    , format(_format)
    , data(_data)
{}

Image Image::load_from_file(const std::string& path)
{
    Image img;
    int width, height, nrComponents;
    uint8_t* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if(data != nullptr)
    {
        size_t size = width * height * nrComponents;
        std::vector<uint8_t> imgData(data, data + size);
        img = Image(width, height, false, nrComponents, imgData);
        stbi_image_free(data); // Don't forget to free the allocated memory
    }
    else
    {

    }
    
    return img;
}
}
