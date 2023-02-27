#pragma once
#include "Object.h"
#include "Component.h"
#include <string>
#include <list>
#include <unordered_map>
#include <typeinfo>
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
		TComponent *AddComponent()
		{
			TComponent *component = new TComponent();
			component->SetGameObject(this);
			auto name = type::get(*component).get_name().to_string();
			components[name] = component;
			return component;
		}
		Component *AddComponent(string componentType)
		{
			auto type = type::get_by_name(componentType);
			variant obj = type.create();
			Component *component = obj.get_value<Component *>();
			component->SetGameObject(this);
			components[componentType] = component;
			return component;
		}

		template <typename TComponent>
		void RemoveComponent(TComponent component)
		{
			auto name = type::get(component).get_name().to_string();
			components.erase(name);
			// components.remove(component);
		}

		template <typename TComponent>
		TComponent *GetComponent()
		{
			for (auto &kv : components)
			{
				if (TComponent *target = dynamic_cast<TComponent *>(kv.second))
					return target;
				// cout<<kv.first<<kv.second<<endl;
			}
			// for (Component *component : components)
			// {
			// 	if (TComponent *target = dynamic_cast<TComponent *>(component))
			// 		return target;
			// }
			return NULL;
		}

		std::unordered_map<std::string, Component *> components;
		// std::list<Component *> components;
		string name;
		bool isActive;

	private:
		void SetName(string name);
	};
}