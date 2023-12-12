#pragma once
#include <string>
#include <vector>
#include <core/template/ref.hpp>

namespace Linky {
class Image {
public:
    Image() {}

    //Image(int _width, int _height, bool _mipmaps, int _format);

    Image(int _width, int _height, bool _mipmaps, int _format, const std::vector<uint8_t> &_data);

    ~Image() {}

    static Image load_from_file(const std::string &path);

public:
    int format = 0;
    int width = 0;
    int height = 0;
    std::vector<uint8_t> data;
    bool mipmaps = false;
};
}
