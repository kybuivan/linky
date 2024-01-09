#include <catch2/catch_test_macros.hpp>
#include <core/file/file.hpp>

TEST_CASE ("[file]") {
    std::filesystem::path path1("C://");
    std::string str = linky::file::to_string(path1);    
    REQUIRE(str == "C://");
}