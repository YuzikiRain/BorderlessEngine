#include "Scene.h"
#include <vector>
#include "Render/MeshRenderer.h"
#include "Render/MeshFilter.h"
#include "Render/Material.h"
#include <yaml-cpp/yaml.h>

namespace BorderlessEngine
{
	Scene::Scene() : name("new scene") {}

	Scene::Scene(const char *name = "new scene")
	{
		this->name = name;
		gameObjects = std::vector<GameObject *>();
	}

	Scene::Scene(const char *name, vector<GameObject *> gameObjects)
	{
		this->name = name;
		this->gameObjects = gameObjects;
	}

	void Scene::AddEmptyGameObject()
	{
		this->gameObjects.push_back(new GameObject());
	}

	void Scene::AddCube()
	{
		auto cubeGameObject = new GameObject();
		auto meshRenderer = cubeGameObject->AddComponent<MeshRenderer>();
		auto meshFilter = cubeGameObject->AddComponent<MeshFilter>();
		meshFilter->Model = new Model("Assets/Model/nanosuit/nanosuit.obj");
		auto material = cubeGameObject->AddComponent<Material>();
		material->shader = new Shader("F:/ForkSource/BorderlessEngine/Shader/unlit.vs", "F:/ForkSource/BorderlessEngine/Shader/unlit.fs");
		printf(meshFilter->Model->Name.c_str());
		this->gameObjects.push_back(cubeGameObject);
	}

	vector<GameObject *> Scene::GetAllGameObjects()
	{
		return this->gameObjects;
	}
}