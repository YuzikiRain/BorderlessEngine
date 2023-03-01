#include <string>
#include <cstring>
#include "GameObject.h"

using std::string;

namespace BorderlessEngine
{
	GameObject::GameObject(string newName, bool isActive)
	{
		SetName(newName);
		this->isActive = isActive;
	}

	void GameObject::SetName(string name)
	{
		this->name = name;
	}
}