#pragma once
#include <string>
#include <core/object/object_id.hpp>
#include <core/variant/variant.hpp>

namespace Linky {
struct PropertyInfo {
    Variant::Type type = Variant::NIL;
    std::string name;

    PropertyInfo() {}
    PropertyInfo(const Variant::Type _type, const std::string _name)
        : type(_type)
        , name(_name)
    {}
};

class Object {
public:
    Object();
private:
    ObjectID mObjectID;
};
}