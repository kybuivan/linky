#include <catch2/catch_test_macros.hpp>
#include <core/io/logger.hpp>

TEST_CASE("[logger]")
{
    LINKY_SET_LOG_LEVEL(info);
    LINKY_DEBUG("Test debug");
}