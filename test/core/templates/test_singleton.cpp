#include <catch2/catch_test_macros.hpp>
#include <core/templates/singleton.hpp>

namespace linky::core {
class singleton_test : public singleton<singleton_test> {
private:
    friend singleton;
};

class singleton_non {

};
TEST_CASE("[singleton] empty") {
    singleton_test test = singleton_test();

    singleton_test::get();
    singleton_non& test2 = singleton<singleton_non>::get();
}
}