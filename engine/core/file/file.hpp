#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace linky::file {
auto to_string(const std::filesystem::path& path) -> std::string;

auto from_string(const std::string& path) -> std::filesystem::path;

// return value will be empty if file does not exist, or is not regular file, or is empty
[[nodiscard]] auto read(
    const std::string_view       description,
    const std::filesystem::path& path
) -> std::optional<std::string>;

[[nodiscard]] auto check_is_existing_non_empty_regular_file(
    const std::string_view       description,
    const std::filesystem::path& path
) -> bool;

}