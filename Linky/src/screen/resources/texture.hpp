#pragma once
#include <string>
#include <iostream>

namespace Linky
{
class Texture
{
public:
    unsigned int id;
    int width;
    int height;
    int components;
    std::string name;
    std::string path;
};
}