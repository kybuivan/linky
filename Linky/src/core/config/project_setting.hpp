#pragma once
#include <string>
#include <filesystem>

namespace linky {
namespace core {
struct project_config {
    std::string name = "Untitled";
    int width = 1400;
    int height = 900;
    bool fullscreen = false;
};

class project_setting {
public:
    project_setting() = default;

    project_config& get_config() { return m_config; }
    
private:
    project_config m_config;
};
}
}