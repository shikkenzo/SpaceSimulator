#pragma once
#include "Application.h"
#include "Scene.h"

class GameApp : public Application
{
public:
	void Init() override;
	void Update(float deltaTime) override;
	void Shutdown() override;
private:
	/*Object& CreateObject();
	void DestroyObject(Object& object);*/
};
