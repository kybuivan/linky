#pragma once
#include <string>
#include <filesystem>

namespace Linky {
struct ProjectConfig {
    std::string name = "Untitled";
    int width = 1400;
    int height = 900;
    bool fullscreen = false;
};

class ProjectSetting {
public:
    ProjectSetting() = default;

    ProjectConfig& get_config() { return m_config; }
    
private:
    ProjectConfig m_config;
};
}