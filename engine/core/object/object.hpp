// Copyright (c) 2023-2024 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <iostream>
#include <core/object/object_id.hpp>
#include <core/templates/ref.hpp>
#include <core/variant/variant.hpp>
#include <entt/entity/registry.hpp>

namespace linky {
namespace core {
struct property_info {
    variant::type type = variant::type_nil;
    std::string name;
    dictionary data;

    property_info() {}
    property_info(const variant::type _type, const std::string _name)
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

    auto get_parrent() const -> entt::entity;
    auto get_children() const -> std::vector<entt::entity>;

    virtual void add(object *component) {}
    virtual void remove(object *component) {}
private:
    std::unordered_map<std::string, variant> m_properties;
    entt::registry* m_registry;
    entt::entity m_entity;
    object_id m_object_id;
    object *m_parrent;
};
}
}