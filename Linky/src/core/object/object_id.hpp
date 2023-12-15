#pragma once
#include <core/typedefs.h>

namespace Linky {
class ObjectID {
public:
    ObjectID();

    uint64_t operator()() const { return mID; }
private:
    uint64_t mID = 0;
};
}