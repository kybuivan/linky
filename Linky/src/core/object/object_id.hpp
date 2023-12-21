#pragma once
#include <core/typedefs.hpp>

namespace linky {
namespace core {
class object_id {
public:
    object_id();

    std::uint64_t operator()() const { return mID; }
private:
    std::uint64_t mID = 0;
};
}
}