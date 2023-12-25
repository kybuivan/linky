#include <catch2/catch_test_macros.hpp>
#include <core/error/errordefs.hpp>

namespace linky::core {

TEST_CASE("error defs")
{
    error err = error::ok;

    REQUIRE(err == error::ok);
}
}
