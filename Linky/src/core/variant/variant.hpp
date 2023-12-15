#pragma once
#include "core/typedefs.h"

namespace Linky {
class Variant {
public:
    enum Type {
        NIL,

        BOOL,
        INT,
        FLOAT,
        STRING,

        VARIANT_MAX
    };
    
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