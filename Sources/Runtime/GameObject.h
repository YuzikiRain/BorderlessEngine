#pragma once
#include "Object.h"
#include "Component.h"
#include <list>
#include <typeinfo>

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
			if (Object *o = dynamic_cast<Object *>(component))
			{
				o->Name = (typeid(component).name());
			}
			components.emplace_back(component);
			return component;
		}

		template <typename TComponent>
		void RemoveComponent(TComponent component)
		{
			components.remove(component);
		}

		template <typename TComponent>
		TComponent *GetComponent()
		{
			for (Component *component : components)
			{
				if (TComponent *target = dynamic_cast<TComponent *>(component))
					return target;
			}
			return NULL;
		}
		std::list<Component *> components;
		char *name;
		bool isActive;

	private:
		void SetName(const char *name);
	};
}