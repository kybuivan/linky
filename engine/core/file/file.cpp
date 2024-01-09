#include "file.hpp"

namespace linky::file {
auto to_string(const std::filesystem::path& path) -> std::string
{
    auto utf8 = path.u8string();
    auto s = std::string(reinterpret_cast<char const*>(utf8.data()), utf8.size());
    return s;
}

auto from_string(const std::string& path) -> std::filesystem::path
{
    return std::filesystem::u8path(path);
}

// return value will be empty if file does not exist, or is not regular file, or is empty
[[nodiscard]] auto read(
    const std::string_view       description,
    const std::filesystem::path& path
) -> std::optional<std::string>
{
    const bool file_is_ok = check_is_existing_non_empty_regular_file(description, path);
    if (!file_is_ok) {
        return {};
    }

    const std::size_t file_length = std::filesystem::file_size(path);
    std::FILE* file =
    std::fopen(to_string(path).c_str(), "rb");

    if (file == nullptr) {
        return {};
    }

    std::size_t bytes_to_read = file_length;
    std::size_t bytes_read = 0;
    std::string result(file_length, '\0');
    do {
        const auto read_byte_count = std::fread(result.data() + bytes_read, 1, bytes_to_read, file);
        if (read_byte_count == 0) {
            return {};
        }
        bytes_read += read_byte_count;
        bytes_to_read -= read_byte_count;
    } while (bytes_to_read > 0);

    std::fclose(file);

    return std::optional<std::string>(result);
}

[[nodiscard]] auto check_is_existing_non_empty_regular_file(
    const std::string_view       description,
    const std::filesystem::path& path
) -> bool
{
    std::error_code error_code;
    const bool exists = std::filesystem::exists(path, error_code);
    if (error_code) {
        return false;
    }
    if (!exists) {
        return false;
    }
    const bool is_regular_file = std::filesystem::is_regular_file(path, error_code);
    if (error_code) {
        return false;
    }
    if (!is_regular_file) {
        return false;
    }
    const bool is_empty = std::filesystem::is_empty(path, error_code);
    if (error_code) {
        return {};
    }
    if (is_empty) {
        return false;
    }
    return true;
}
}
