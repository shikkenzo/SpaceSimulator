#pragma once

#include <memory>



struct Object;

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Update(float deltaTime, Object& object)
    {
    }

    virtual  size_t* GetType() const = 0;

    virtual std::unique_ptr<Component> Clone() const = 0;
};


template<typename T>
class ComponentImpl : public Component
{
public:
    inline static size_t Type;

    size_t* GetType() const override
    {
        return &Type;
    }

    std::unique_ptr<Component> Clone() const override
    {
        return std::make_unique<T>(static_cast<const T&>(*this));
    }
};
