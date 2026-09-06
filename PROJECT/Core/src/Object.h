#pragma once

#include "Components/Component.h"

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>



struct Object
{
public:
    Object() = default;
    Object(const Object& other);

    Object& operator=(const Object&) = delete;
    Object(Object&&) = delete;
    Object& operator=(Object&&) = delete;

    void CopyChildrenFrom(const Object& object);
    void CopyComponentsFrom(const Object& object);

public:
    void Update(float deltaTime);

public:
    void AddChild(std::unique_ptr<Object> child);
    std::unique_ptr<Object> RemoveChild(Object& child);
    Object* GetParent() const;

    template<typename Func>
    void ForEachChild(Func&& func) const
    {
        for (const auto& child : m_children)
            func(*child);
    }

public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        if (GetComponent<T>())
            throw std::runtime_error("Object::AddComponent(): component has already been added");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *component;
        m_components.emplace(component->GetType(), std::move(component));
        return ref;
    }

    template<typename T>
    T* GetComponent() const
    {
        auto it = m_components.find(&T::Type);
        if (it == m_components.end())
            return nullptr;

        return static_cast<T*>(it->second.get());
    }

    template<typename T>
    T& RequireComponent()
    {
        T* component = GetComponent<T>();

        if (!component)
            throw std::runtime_error("Object::RequireComponent(): object is missing required component");

        return *component;
    }

private:
    std::unordered_map<const void*, std::unique_ptr<Component>> m_components;
    std::vector<std::unique_ptr<Object>> m_children;
    Object* m_parent = nullptr;
};
