#include "engine.hpp"
#include "core/version.hpp"

namespace linky::core {
version_info engine::get_version_info() const {
    version_info ver;
    ver.m_major = LINKY_MAJOR_VERSION;
    ver.m_minor = LINKY_MINOR_VERSION;
    ver.m_patch = LINKY_PATCH_VERSION;
    ver.m_commit = LINKY_COMMIT_HASH;
    std::cout << ver.m_commit << std::endl;
    return ver;
}
}