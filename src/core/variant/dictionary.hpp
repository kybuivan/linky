#pragma once
#include <map>
#include <core/string/string.hpp>
#include <core/templates/ref.hpp>

namespace linky {
namespace core {
class variant;
using dictionary = std::map<std::string, std::unique_ptr<variant>>;
}
}