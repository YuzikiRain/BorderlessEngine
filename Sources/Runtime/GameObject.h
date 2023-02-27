#pragma once
#include "Object.h"
#include "Component.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <rttr/registration>
using namespace rttr;

using namespace std;

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject(string newName = "New GameObject", bool isActive = true);
		~GameObject();
		template <typename TComponent>
		TComponent &AddComponent()
		{
			shared_ptr<TComponent> componentPointer = make_shared<TComponent>();
			componentPointer->SetGameObject(this);
			auto name = type::get(*componentPointer).get_name().to_string();
			components[name] = componentPointer;
			return *componentPointer;
		}
		Component &AddComponent(string componentType)
		{
			auto type = type::get_by_name(componentType);
			variant obj = type.create();
			shared_ptr<Component> componentPointer = obj.get_value<shared_ptr<Component>>();
			componentPointer->SetGameObject(this);
			components[componentType] = componentPointer;
			return *componentPointer;
		}

		template <typename TComponent>
		void RemoveComponent(TComponent component)
		{
			auto name = type::get(component).get_name().to_string();
			components.erase(name);
		}

		template <typename TComponent>
		TComponent &GetComponent()
		{
			try
			{
				for (auto &kv : components)
				{
					if (shared_ptr<TComponent> target = dynamic_pointer_cast<TComponent>(kv.second))
						return *target;
				}
				throw runtime_error("can't find component of type");
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		// std::unordered_map<std::string, Component *> components;
		std::unordered_map<std::string, shared_ptr<Component>> components;
		string name;
		bool isActive;

	private:
		void SetName(string name);
	};
}