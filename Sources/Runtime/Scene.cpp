#include "Scene.h"
#include <vector>
#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "Material.h"
#include "Transform.h"
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
		auto transform = cubeGameObject->AddComponent<Transform>();
		auto meshRenderer = cubeGameObject->AddComponent<MeshRenderer>();
		auto meshFilter = cubeGameObject->AddComponent<MeshFilter>();
		meshFilter->Model = new Model("D:/GitReposity/BorderlessEngine/Assets/Model/nanosuit/nanosuit.obj");
		auto material = cubeGameObject->AddComponent<Material>();
		material->shader = new Shader("D:/GitReposity/BorderlessEngine/Shader/unlit.vs", "D:/GitReposity/BorderlessEngine/Shader/unlit.fs");
		// printf(meshFilter->Model->Name.c_str());
		this->gameObjects.push_back(cubeGameObject);
	}

	vector<GameObject *> Scene::GetAllGameObjects()
	{
		return this->gameObjects;
	}
}