#pragma once
#include <iostream>
#include <string>
#include <map>
#include <core/object/object_id.hpp>
#include <core/template/ref.hpp>
#include <core/variant/variant.hpp>

namespace linky {
namespace core {
using Dictionary = std::map<std::string, Ref<variant>>;
struct PropertyInfo {
    variant::Type type = variant::NIL;
    std::string name;
    Dictionary data;

    PropertyInfo() {}
    PropertyInfo(const variant::Type _type, const std::string _name)
        : type(_type)
        , name(_name)
    {}
};

class object {
public:
    object();
    virtual ~object();

    void render() { std::cout << "object ID:" << m_object_id() << " is render\n";}
    object_id get_instance_id() const { return m_object_id; }
    void set_parrent(object * parrent) { m_parrent = parrent; }

    object * get_parrent() { return m_parrent;}

    virtual void add(object *component) {}
    virtual void remove(object *component) {}
private:

    object_id m_object_id;
    object *m_parrent;
};
}
}