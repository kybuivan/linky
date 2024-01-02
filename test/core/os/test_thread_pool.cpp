#include <catch2/catch_test_macros.hpp>
#include <core/os/thread_pool.hpp>

namespace linky::core {
TEST_CASE ("[thread pool]") {
    thread_pool pool = thread_pool();
    int g = 0;
    // for(int i = 0; i < 10; i++)
    // {
    //     pool.add([&](){
    //             g++;
    //         });
    // }
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    REQUIRE(g == 0);
}
}