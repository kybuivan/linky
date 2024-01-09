#include <catch2/catch_test_macros.hpp>
#include <core/debug/profiler.hpp>

int add(int a, int b)
{
    LINKY_PROFILE("add");
    return a + b;
}

int plus2(int a)
{
    LINKY_PROFILE("plus2");
    return a + 2;
}

TEST_CASE("[profiler] profile")
{
    REQUIRE(add(1, 2) == 3);
    REQUIRE(plus2(1) == 3);
}
