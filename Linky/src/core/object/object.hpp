#pragma once
#include <iostream>
#include <core/object/object_id.hpp>
#include <core/templates/ref.hpp>
#include <core/variant/variant.hpp>

namespace linky {
namespace core {
struct property_info {
    variant::type m_type = variant::type_nil;
    std::string m_name;
    dictionary m_data;

    property_info() {}
    property_info(const variant::type type, const std::string name)
        : m_type(type)
        , m_name(name)
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