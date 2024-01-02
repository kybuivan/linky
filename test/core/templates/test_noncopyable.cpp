#include <catch2/catch_test_macros.hpp>
#include <core/templates/noncopyable.hpp>

namespace linky::core {
class noncopyable_test : public noncopyable {
};

class noncopyable_non {

};
TEST_CASE("[noncopyable] empty") {
    noncopyable_test test; // ok
    noncopyable_test test1 = noncopyable_test(); // ok
    //noncopyable_non& test2 = test; // error
    //noncopyable_non test2(test1); // error
}
}