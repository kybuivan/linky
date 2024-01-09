#include <catch2/catch_test_macros.hpp>
#include "core/parser/parser.hpp"

using json = nlohmann::json;

struct person {
    std::string name;
    std::string address;
    int age;
};

TEST_CASE("[parser]") {
    person p = {"Ned Flanders", "744 Evergreen Terrace", 60};

    // convert to JSON: copy each value into the JSON object
    json j;
    j["name"] = p.name;
    j["address"] = p.address;
    j["age"] = p.age;

    // convert from JSON: copy each value from the JSON object
    person p1 {
        j["name"].template get<std::string>(),
        j["address"].template get<std::string>(),
        j["age"].template get<int>()
    };

    REQUIRE(p1.name == p.name);
    REQUIRE(p1.address == p.address);
    REQUIRE(p1.age == p.age);
}