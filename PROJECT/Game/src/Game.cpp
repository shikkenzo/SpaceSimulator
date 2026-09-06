#include "Game.h"

#include "Graphics/SphereMesh.h"

#include "Object.h"
#include "Components/Components.h"
#include "ResourceManager.h"

#include <iostream>

void GameApp::Init()
{
	Object& camera = m_scene.CreateObject();

	camera.AddComponent<TransformComponent>().localPosition() = glm::vec3(-150.0f, 50.0f, 150.0f);
	camera.RequireComponent<TransformComponent>().localRotation() = glm::rotate(camera.RequireComponent<TransformComponent>().localRotation(), glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	camera.AddComponent<CameraComponent>();
	m_scene.SetActiveCamera(camera);

	camera.AddComponent<FreeCameraController>();


#pragma region assets
	auto sphere = GenerateSphere(1.0f, 16, 16);

	auto defaultShader = ResourceManager::LoadShader("assets/shaders/default.vert", "assets/shaders/default.frag");
	auto defaultTexture = ResourceManager::LoadTexture("assets/textures/rock.png");
	auto sunTexture = ResourceManager::LoadTexture("assets/textures/sun.png");
	auto planetTexture = ResourceManager::LoadTexture("assets/textures/planet.png");

	auto defaultMaterial = ResourceManager::RegisterMaterial("defaultMaterial", std::make_shared<Material>(defaultShader, defaultTexture));
	auto sunMaterial = ResourceManager::RegisterMaterial("sunMaterial", std::make_shared<Material>(defaultShader, sunTexture));
	auto planetMaterial = ResourceManager::RegisterMaterial("planetMaterial", std::make_shared<Material>(defaultShader, planetTexture));

	auto mesh = ResourceManager::RegisterMesh("sphere", std::make_shared<Mesh>(sphere.vertices, sphere.indices));
#pragma endregion


	Object& obj1 = m_scene.CreateObject();
	obj1.AddComponent<StaticMeshComponent>();
	obj1.AddComponent<TransformComponent>();
	obj1.RequireComponent<StaticMeshComponent>().meshData = mesh;
	obj1.RequireComponent<StaticMeshComponent>().material = sunMaterial;
	obj1.RequireComponent<TransformComponent>().localPosition() = glm::vec3(0.0f, 0.0f, 0.0f);
	obj1.RequireComponent<TransformComponent>().localScale() = glm::vec3(100.0f);


	Object& obj2 = m_scene.CreateObject();
	m_scene.AttachChild(obj1, obj2);
	obj2.AddComponent<StaticMeshComponent>();
	obj2.AddComponent<TransformComponent>().localScale() = glm::vec3(5.0f);
	obj2.RequireComponent<StaticMeshComponent>().meshData = mesh;
	obj2.RequireComponent<StaticMeshComponent>().material = planetMaterial;
	OrbitComponent& orbit2 = obj2.AddComponent<OrbitComponent>(obj1.RequireComponent<TransformComponent>().transform());
	orbit2.orbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	orbit2.radius = 1000.0f;
	orbit2.angularSpeed = 6.0f;

	Object& obj3 = m_scene.CreateObject();
	m_scene.AttachChild(obj1, obj3);
	obj3.AddComponent<StaticMeshComponent>();
	obj3.AddComponent<TransformComponent>();
	obj3.RequireComponent<StaticMeshComponent>().meshData = mesh;
	obj3.RequireComponent<StaticMeshComponent>().material = defaultMaterial;
	OrbitComponent& orbit3 = obj3.AddComponent<OrbitComponent>(obj2.RequireComponent<TransformComponent>().transform());
	orbit3.orbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	orbit3.radius = 100.0f;
	orbit3.angularSpeed = 125.0f;

	Object& obj4 = m_scene.CreateObject();
	m_scene.AttachChild(obj1, obj4);
	obj4.AddComponent<StaticMeshComponent>();
	obj4.AddComponent<TransformComponent>().localScale() = glm::vec3(2.5f);
	obj4.RequireComponent<StaticMeshComponent>().meshData = mesh;
	obj4.RequireComponent<StaticMeshComponent>().material = planetMaterial;
	OrbitComponent& orbit4 = obj4.AddComponent<OrbitComponent>(obj1.RequireComponent<TransformComponent>().transform());
	orbit4.orbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	orbit4.radius = 2000.0f;
	orbit4.angularSpeed = 2.0f;

	Object& obj5 = m_scene.CreateObject();
	m_scene.AttachChild(obj1, obj5);
	obj5.AddComponent<StaticMeshComponent>();
	obj5.AddComponent<TransformComponent>().localScale() = glm::vec3(2.5f);
	obj5.RequireComponent<StaticMeshComponent>().meshData = mesh;
	obj5.RequireComponent<StaticMeshComponent>().material = defaultMaterial;
	OrbitComponent& orbit5 = obj5.AddComponent<OrbitComponent>(obj1.RequireComponent<TransformComponent>().transform());
	orbit5.orbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	orbit5.radius = 1500.0f;
	orbit5.angularSpeed = 4.0f;
}

void GameApp::Update(float deltaTime)
{
	std::cout << "FPS: " << (1.0f / deltaTime) << std::endl;

	m_scene.ForEachObject([&](Object& object)
		{
			object.Update(deltaTime);
		});

	m_scene.ProcessDestroyQueue();
}

void GameApp::Shutdown()
{
	m_scene.Clear();
}

//Object& GameApp::CreateObject()
//{
//	return m_scene->CreateObject();
//}
//
//void GameApp:: DestroyObject(Object& object)
//{
//	m_scene->DestroyObject(object);
//}
