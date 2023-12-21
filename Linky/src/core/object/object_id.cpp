#include "object_id.hpp"
#include <random>

namespace linky {
namespace core {
static std::random_device randomDevice;
static std::mt19937_64 randomEngine(randomDevice());
static std::uniform_int_distribution<uint64_t> uniformDistribution(0, (std::numeric_limits<uint64_t>::max)());

object_id::object_id() {
    mID = uniformDistribution(randomEngine);
}
}
}