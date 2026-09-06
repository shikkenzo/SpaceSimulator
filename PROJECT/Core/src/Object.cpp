#include "Object.h"



Object::Object(const Object& other)
{
    CopyComponentsFrom(other);
    CopyChildrenFrom(other);
}

void Object::CopyChildrenFrom(const Object& object)
{
    m_children.clear();
    m_children.reserve(object.m_children.size());

    for (const auto& child : object.m_children)
    {
        auto copy = std::make_unique<Object>(*child);

        AddChild(std::move(copy));
    }
}

void Object::CopyComponentsFrom(const Object& object)
{
    m_components.clear();
    m_components.reserve(object.m_components.size());

    for (const auto& [key, component] : object.m_components)
        m_components.emplace(key, component->Clone());
}

void Object::Update(float deltaTime)
{
    for (auto& [_, component] : m_components)
        component->Update(deltaTime, *this);
}

void Object::AddChild(std::unique_ptr<Object> child)
{
    if (!child)
        throw std::runtime_error("Object::AddChild(): child is null");

    if (child.get() == this)
        throw std::runtime_error("Object::AddChild(): an object cannot be its own child");

    if (child->m_parent)
        throw std::runtime_error("Object::AddChild(): child already has a parent");

    child->m_parent = this;
    m_children.push_back(std::move(child));
}

std::unique_ptr<Object> Object::RemoveChild(Object& child)
{
    for (auto it = m_children.begin(); it != m_children.end(); ++it)
    {
        if (it->get() == &child)
        {
            auto result = std::move(*it);
            m_children.erase(it);
            result->m_parent = nullptr;
            return result;
        }

        if (auto result = (*it)->RemoveChild(child))
            return result;
    }

    return nullptr;
}

Object* Object::GetParent() const
{
    return m_parent;
}
