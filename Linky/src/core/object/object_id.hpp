#pragma once
#include <core/typedefs.h>

namespace Linky {
class ObjectID {
public:
    ObjectID();
private:
    uint64_t mID = 0;
};
}