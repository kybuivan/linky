// Copyright (c) 2023 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "core/io/image_loader.hpp"
#include <filesystem>
#include <format>
#include <stb_image.h>

namespace linky {
namespace core {
namespace fs = std::filesystem;

auto image_loader::load_stb_image(const std::string& path, int& width, int& height, int& nrComponents) -> std::expected<unsigned char*, std::string> {
    
    const auto filePath = fs::path(path);

    if (!fs::exists(filePath))
    {
        return std::unexpected{std::format("Cannot load file: '{}'", filePath.string())};
    }

    auto pixels = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    
    return pixels;
}
}
}
