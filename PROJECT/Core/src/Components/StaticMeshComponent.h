#pragma once

#include "Component.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"

#include <memory>



struct StaticMeshComponent : public ComponentImpl<StaticMeshComponent>
{
	std::shared_ptr<Mesh> meshData;
	std::shared_ptr<Material> material;
};