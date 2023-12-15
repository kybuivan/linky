#pragma once
#include <iostream>
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
    virtual ~Object();

    void render() { std::cout << "Object ID:" << mObjectID() << " is render\n";}
    ObjectID get_instance_id() const { return mObjectID; }
    void set_parrent(Object * parrent) { mParrent = parrent; }

    Object * get_parrent() { return mParrent;}

    virtual void add(Object *component) {}
    virtual void remove(Object *component) {}
private:
    ObjectID mObjectID;
    Object *mParrent;
};
}