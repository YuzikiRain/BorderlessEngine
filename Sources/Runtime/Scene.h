#pragma once
#include "GameObject.h"
#include "Object.h"
#include <vector>
using std::vector;

namespace BorderlessEngine
{
	class Scene : public Object
	{
	public:
		Scene();
		Scene(const char *name);
		Scene(const char *name, vector<GameObject *> gameObjects);
		void AddEmptyGameObject();
		void AddCube();
		vector<GameObject *> GetAllGameObjects();
		const char *name;

        YAML::Node Serialize() override {
            YAML::Node node;
            node["name"] = Name;
            return node;
        }

	private:
		mutable std::vector<GameObject *> gameObjects;
	};
}