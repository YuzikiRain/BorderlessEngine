#pragma once
#include "Object.h"
#include "Component.h"
#include <string>
#include <list>
#include <unordered_map>
#include <typeinfo>
#include <rttr/registration>
using namespace rttr;

namespace BorderlessEngine
{
	class GameObject : public Object
	{
	public:
		GameObject(const char *newName = "New GameObject", bool isActive = true);
		~GameObject();
		template <typename TComponent>
		TComponent *AddComponent()
		{
			TComponent *component = new TComponent();
			auto name = type::get(*component).get_name().to_string();
			// if (Object *o = dynamic_cast<Object *>(component))
			// {
			// 	o->Name = (typeid(component).name());
			// }
			components[name] = component;
			// components.emplace_back(component);
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
		char *name;
		bool isActive;

	private:
		void SetName(const char *name);
	};
}