#pragma once
#include <string>
#include <iostream>

namespace linky
{
class texture
{
public:
    unsigned int m_id;
    int m_width;
    int m_height;
    int m_components;
    std::string m_name;
    std::string m_path;
};
}