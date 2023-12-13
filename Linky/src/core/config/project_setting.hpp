#pragma once
#include <string>
#include <filesystem>

namespace Linky {
struct ProjectConfig {
    std::string name = "Untitled";
};

class ProjectSetting {
public:
    ProjectSetting() = default;

    ProjectConfig& get_config() { return m_config; }
    
private:
    ProjectConfig m_config;
};
}