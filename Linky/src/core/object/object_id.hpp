#pragma once
#include <core/typedefs.hpp>

namespace linky {
namespace core {
class object_id {
public:
    object_id();

    std::uint64_t operator()() const { return m_id; }
private:
    std::uint64_t m_id = 0;
};
}
}