#include "Scene.h"

#include "Components/TransformComponent.h"

#include <algorithm>
#include <stdexcept>



namespace
{
    bool ContainsAddress(const Object& root, const Object* target)
    {
        if (&root == target)
            return true;

        bool found = false;
        root.ForEachChild([&](const Object& child)
        {
            if (!found)
                found = ContainsAddress(child, target);
        });
        return found;
    }

    bool ContainsObject(const Object& root, const Object& target)
    {
        return ContainsAddress(root, &target);
    }
}

Scene::Scene()
    : m_root(std::make_unique<Object>())
{
}

Object& Scene::CreateObject()
{
    auto object = std::make_unique<Object>();
    Object& reference = *object;
    m_root->AddChild(std::move(object));
    return reference;
}

Object& Scene::CloneObject(Object& object)
{
    if (!ContainsObject(*m_root, object))
        throw std::runtime_error("Scene::CloneObject(): object does not belong to this scene");

    auto copy = std::make_unique<Object>(object);
    Object& reference = *copy;
    object.GetParent()->AddChild(std::move(copy));
    return reference;
}

void Scene::DestroyObject(Object& object)
{
    if (&object == m_root.get())
        throw std::runtime_error("Scene::DestroyObject(): the scene root cannot be destroyed");

    if (!ContainsObject(*m_root, object))
        return;

    if (std::find(m_destroyQueue.begin(), m_destroyQueue.end(), &object) == m_destroyQueue.end())
        m_destroyQueue.push_back(&object);
}

void Scene::ProcessDestroyQueue()
{
    for (Object* object : m_destroyQueue)
    {
        if (!object || object == m_root.get())
            continue;

        if (!ContainsAddress(*m_root, object))
            continue;

        if (m_activeCamera && ContainsAddress(*object, m_activeCamera))
            m_activeCamera = nullptr;

        m_root->RemoveChild(*object);
    }

    m_destroyQueue.clear();
}

void Scene::AttachChild(Object& parent, Object& child)
{
    if (&parent == &child)
        throw std::runtime_error("Scene::AttachChild(): an object cannot be attached to itself");

    if (!ContainsObject(*m_root, parent) || !ContainsObject(*m_root, child))
        throw std::runtime_error("Scene::AttachChild(): both objects must belong to the scene");

    if (ContainsObject(child, parent))
        throw std::runtime_error("Scene::AttachChild(): cannot create a hierarchy cycle");

    std::unique_ptr<Object> object = m_root->RemoveChild(child);
    if (object)
        parent.AddChild(std::move(object));
}

void Scene::DetachObject(Object& object)
{
    if (&object == m_root.get())
        return;

    AttachChild(*m_root, object);
}

void Scene::SetActiveCamera(Object& object)
{
    if (!ContainsObject(*m_root, object))
        throw std::runtime_error("Scene::SetActiveCamera(): camera object is not in this scene");

    m_activeCamera = &object;
}

Object* Scene::GetActiveCamera() const
{
    if (!m_activeCamera)
        throw std::runtime_error("Scene::GetActiveCamera(): there's no active camera in the current scene");

    return m_activeCamera;
}

Object& Scene::GetRoot()
{
    return *m_root;
}

void Scene::Clear()
{
    m_destroyQueue.clear();
    m_activeCamera = nullptr;
    m_root = std::make_unique<Object>();
}
