#pragma once
#include <core/typedefs.hpp>

namespace Linky {
class ObjectID {
public:
    ObjectID();

    std::uint64_t operator()() const { return mID; }
private:
    std::uint64_t mID = 0;
};
}