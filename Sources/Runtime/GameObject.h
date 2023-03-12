#pragma once

#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <rttr/registration>

using namespace rttr;

#include "yaml-cpp/yaml.h"
#include "ISerializable.h"

using BorderlessEngine::GameObject;
using std::shared_ptr;
using std::string;

namespace BorderlessEngine {
    class GameObject : public Object {
    public:
        GameObject(string newName = "New GameObject", bool isActive = true);

        ~GameObject() {};

        template<typename TComponent>
        TComponent &AddComponent() {
            shared_ptr<TComponent> componentPointer = std::make_shared<TComponent>();
            componentPointer->SetGameObject(this);
            auto name = type::get(*componentPointer).get_name().to_string();
            components[name] = componentPointer;
            return *componentPointer;
        }

        Component &AddComponent(string componentType) {
            auto type = type::get_by_name(componentType);
            variant obj = type.create();
            shared_ptr<Component> componentPointer = obj.get_value<shared_ptr<Component>>();
            componentPointer->SetGameObject(this);
            components[componentType] = componentPointer;
            return *componentPointer;
        }

        template<typename TComponent>
        void RemoveComponent(TComponent component) {
            auto name = type::get(component).get_name().to_string();
            components.erase(name);
        }

        template<typename TComponent>
        TComponent &GetComponent() {
            try {
                for (auto &kv: components) {
                    if (shared_ptr<TComponent> target = std::dynamic_pointer_cast<TComponent>(kv.second))
                        return *target;
                }
                throw std::runtime_error("can't find component of type");
            }
            catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
            }
        }

        Component &GetComponent(string componentType) {
            try {
                for (auto &kv: components) {
                    if (type::get_by_name(componentType) == type::get(kv.second))
                        return *kv.second;
                }
                throw std::runtime_error("can't find component of type");
            }
            catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
            }
        }

        YAML::Node Serialize() override {
            YAML::Node node;
            YAML::Node nodeGameObject;
            nodeGameObject["name"] = Name;
            node["gameObject"].push_back(nodeGameObject);
            for (auto &pair: components) {
                auto componentName = pair.first;
                auto component = pair.second;
                node[componentName + "s"].push_back(component->Serialize());
                if (auto t = std::dynamic_pointer_cast<Transform>(component)) {
                    for (int i = 0; i < t->Children.size(); ++i) {
                        auto &child = t->Children[i];
                        auto g = child->GetGameObject();
                        auto test = g->Serialize();
                        node["gameObjects"].push_back(test);
                    }
                }
            }
// GetComponent<Transform>().Parent.
            // node[""] =

            return node;
        }

        std::unordered_map<std::string, shared_ptr < Component>> components;
        bool isActive;

    private:
        void SetName(string name);
    };
}

// namespace YAML
// {
// 	template <>
// 	struct convert<GameObject>
// 	{
// 		static Node encode(const GameObject &gameObject)
// 		{
// 			Node node;
// 			node["name"] = gameObject.name;
// 			for (auto &pair : gameObject.components)
// 			{
// 				auto componentName = pair.first;
// 				auto component = pair.second;
// 				node[componentName + "s"].push_back((*component).Serialize());
// 			}
// 			return node;
// 		}

// 		static bool decode(const Node &node, GameObject &rhs)
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