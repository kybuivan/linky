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

auto read_file(const std::string& path) -> std::string
{
    std::string str;
    std::ifstream in(path, std::ios::binary);

    if(in)
    {
        in.seekg(0, std::ios::end);
        str.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&str[0], str.size());
        in.close();
    }
    return str;
}
}