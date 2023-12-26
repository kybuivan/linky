#pragma once
#include <core/string/string.hpp>
#include <core/io/file_stream.hpp>
#include <core/object/object.hpp>

namespace linky {
namespace core {

class project_settings : public object {
public:
    project_settings();
    ~project_settings();
private:
};
}
}