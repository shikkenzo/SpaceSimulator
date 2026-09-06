#include "Renderer.h"

#include "Scene.h"
#include "Object.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"

#include <glad/glad.h>

#include <iostream>
#include <stdexcept>



void Renderer::Init()
{
    if (!gladLoadGL())
        throw std::runtime_error("Renderer::Init(): failed to initialize GLAD");

    GLint viewport[4]{};
    glGetIntegerv(GL_VIEWPORT, viewport);

    m_width = viewport[2];
    m_height = viewport[3];

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Renderer::Render(const Scene& scene, float aspectRatio)
{
    Object* cameraObject = scene.GetActiveCamera();

    auto* cameraComponent = cameraObject->GetComponent<CameraComponent>();
    auto* cameraTransform = cameraObject->GetComponent<TransformComponent>();

    if (!cameraComponent || !cameraTransform)
        throw std::runtime_error("Renderer::Render(): active camera requires CameraComponent and TransformComponent");

    cameraComponent->camera().UpdateMatrices(cameraTransform->transform(), aspectRatio);

    scene.ForEachObject([&](const Object& object)
    {
        const auto* meshComponent = object.GetComponent<StaticMeshComponent>();
        const auto* transformComponent = object.GetComponent<TransformComponent>();

        if (!meshComponent || !transformComponent)
            return;

        if (!meshComponent->material)
            throw std::runtime_error("Renderer::Render(): StaticMeshComponent has no Material assigned");

        if (!meshComponent->meshData)
            throw std::runtime_error("Renderer::Render(): StaticMeshComponent has no MeshData assigned");

        Material& material = *meshComponent->material;
        material.Bind();

        material.m_shader->SetMat4("camMatrix", cameraComponent->camera().Projection() * cameraComponent->camera().View());
        material.m_shader->SetMat4("model", transformComponent->GetWorldMatrix(object));

        meshComponent->meshData->Draw();
    });
}

void Renderer::Shutdown()
{
}

void Renderer::SetViewportSize(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void Renderer::Clear()
{
    glClearColor(0.10f, 0.11f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
