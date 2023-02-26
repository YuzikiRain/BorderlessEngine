#include <string>
#include <cstring>
#include "GameObject.h"

using namespace std;

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