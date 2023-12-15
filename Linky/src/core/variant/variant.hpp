#pragma once
#include "core/typedefs.h"

namespace Linky {
class Variant {
public:
    Variant();
private:
    union data
    {
        bool mBool;
        int64_t mInt;
        double mDouble;
        /* data */
    };
};
}