#include <catch2/catch_test_macros.hpp>
#include <core/debugger/debugger_profiler.hpp>

TEST_CASE("debugger profiler")
{
    LINKY_FRAME_BEGIN("debugger");
    LINKY_FRAME_END("debugger");
}
