#pragma once
#include <core/object/object_id.hpp>

namespace Linky {
class Object {
public:
    Object();
private:
    ObjectID mObjectID;
};
}