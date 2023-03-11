#pragma once

#include <rttr/registration>
using namespace rttr;

#include "Object.h"
#include "ISerializable.h"

namespace BorderlessEngine
{
	class GameObject;
	class Component : public Object, public ISerializable
	{
		friend GameObject;

	public:
		// 至少有一个虚函数，否则不会被编译器认为是多态类型而无法将父类转换成子类
		virtual GameObject *GetGameObject() { return GameObject; }
		void SetGameObject(GameObject *gameObject) { this->GameObject = gameObject; }
		YAML::Node Serialize()
		{
			// YAML::Node node;
			// node["base"] = Object::Serialize();

			// return node;

			return Object::Serialize();
		}
	protected:
	private:
		GameObject *GameObject = 0;

		RTTR_ENABLE()
	};
}

// namespace YAML
// {
// 	template <>
// 	struct convert<BorderlessEngine::Component>
// 	{
// 		static Node encode(const BorderlessEngine::Component &component)
// 		{
// 			auto baseNode = component.Object::Serialize();
// 			Node node;
// 			node["object"] = baseNode;

// 			return node;
// 		}

// 		static bool decode(const Node &node, BorderlessEngine::Component &rhs)
// 		{
// 			if (!node.IsSequence())
// 			{
// 				return false;
// 			}

// 			rhs.x = node[0].as<int>();
// 			return true;
// 		}
// 	};
// }