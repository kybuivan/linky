#include "file_stream.hpp"

namespace linky::core {
namespace fs = std::filesystem;

auto get_files_recursive(const std::string_view& dir_path) -> std::vector<std::filesystem::path>
{
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(dir_path))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry.path());
        }
    }

    return files;
}
}