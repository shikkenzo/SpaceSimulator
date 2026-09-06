#pragma once

#include "Object.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>



class Scene
{
public:
    Scene();
public:
    Object& CreateObject();
    Object& CloneObject(Object& object);

    void DestroyObject(Object& object);
    void ProcessDestroyQueue();

    void AttachChild(Object& parent, Object& child);
    void DetachObject(Object& object);

    void SetActiveCamera(Object& object);
    Object* GetActiveCamera() const;

    Object& GetRoot();

    void Clear();

public:
    template<typename Func>
    void ForEachObject(Func&& func) const
    {
        auto visit = [&](const auto& self, const Object& object) -> void
            {
                func(object);

                object.ForEachChild(
                    [&](const Object& child)
                    {
                        self(self, child);
                    });
            };

        visit(visit, *m_root);
    }
    template<typename Func>
    void ForEachObject(Func&& func)
    {
        auto visit = [&](const auto& self, Object& object) -> void
            {
                func(object);

                object.ForEachChild(
                    [&](Object& child)
                    {
                        self(self, child);
                    });
            };

        visit(visit, *m_root);
    }

private:
    std::unique_ptr<Object> m_root;
    std::vector<Object*> m_destroyQueue;

    Object* m_activeCamera = nullptr;
};
