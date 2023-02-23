#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include "GameObject.h"
#include "Transform.h"
#include <queue>

using namespace std;
using namespace BorderlessEngine;

namespace BorderlessEditor
{
    class AssetDatabase
    {
    public:
        template <typename T>
        static T LoadAssetAtPath(std::string path)
        {
        }

        static void SaveAsset(Object *object, string path)
        {
            auto obj = (GameObject*)object;
            if (obj != NULL)
            {
                fstream sceneFileStream;
                sceneFileStream.open(path, ios::out | ios::trunc);
                YAML::Node node;
                // auto obj = (GameObject *)object;
                queue<Transform *> q = queue<Transform *>();
                q.push(obj->GetComponent<Transform>());
                int count = 0;
                while (!q.empty())
                {
                    auto transform = q.back();
                    q.pop();
                    Test(transform, node, count);
                    for (int i = 0; i < transform->Children.size(); i++)
                    {
                        q.push(transform->Children[i]);
                    }
                    count++;
                }
                // Test(obj, node);

                sceneFileStream << node;
                sceneFileStream.close();
            }
            if (typeid(object) == typeid(GameObject*))
            {
                fstream sceneFileStream;
                sceneFileStream.open(path, ios::out | ios::trunc);
                YAML::Node node;
                auto obj = (GameObject *)object;
                queue<Transform *> q = queue<Transform *>();
                q.push(obj->GetComponent<Transform>());
                int count = 0;
                while (!q.empty())
                {
                    auto transform = q.back();
                    q.pop();
                    Test(transform, node, count);
                    for (int i = 0; i < transform->Children.size(); i++)
                    {
                        q.push(transform->Children[i]);
                    }
                    count++;
                }
                // Test(obj, node);

                sceneFileStream << node;
                sceneFileStream.close();
            }
        }

        static void Test(Transform *transform, YAML::Node node, int count)
        {
            auto obj = transform->GetGameObject();
            // node["gameObjects"][count]["id"] = obj->name;
            node["gameObjects"][count]["name"] = obj->name;
            node["gameObjects"][count]["isActive"] = obj->isActive;
            // node["transform"][count]["gameObject"] = obj->childIndex;
            node["transform"][count]["index"] = transform->childIndex;
        }

    private:
        // static Scene *currentScene;
    };
}