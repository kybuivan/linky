#pragma once
#include <core/object/object.hpp>

namespace linky {
namespace core {
struct version_info
{
    uint8_t m_major;
    uint8_t m_minor;
    uint8_t m_patch;
    std::string m_commit;
};

class engine : public object {
public:
    engine() {}
    virtual ~engine() {};

    version_info get_version_info() const;
};
}
}