#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include "GameObject.h"
#include "Transform.h"
#include <iostream>
#include <queue>
#include <fstream>

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

        static void SaveAsset(Object *object, std::string path)
        {
            auto obj = (GameObject *)object;
            if (obj != NULL)
            // if (typeid(object) == typeid(GameObject*))
            {
                std::fstream sceneFileStream;
                sceneFileStream.open(path, std::ios::out | std::ios::trunc);
                YAML::Node node;
                std::queue<Transform> q = std::queue<Transform>();
                q.push(obj->GetComponent<Transform>());
                int count = 0;
                while (!q.empty())
                {
                    auto transform = q.back();
                    q.pop();
                    ProcessGameObject(transform, node, count);
                    for (int i = 0; i < transform.Children.size(); i++)
                    {
                        q.push(*transform.Children[i]);
                    }
                    count++;
                }
                // std::cout << node << std::add_cv_t;
                sceneFileStream << node;
                sceneFileStream.close();
            }
        }

        static void ProcessGameObject(Transform &transform, YAML::Node &node, int count)
        {
            auto obj = transform.GetGameObject();
            YAML::Node g;
            g["name"] = obj->name;
            g["isActive"] = obj->isActive;
            // g[count]["id"] = obj->name;
            node["gameObjects"].push_back(g);
            YAML::Node t;
            t["index"] = transform.childIndex;
            node["transform"].push_back(t);
            // node["transform"][count]["gameObject"] = obj->childIndex;
        }

        static void SetProjectPath(std::string projectPath)
        {
            AssetDatabase::projectPath = projectPath;
        }

        static std::string GetProjectPath()
        {
            return projectPath;
        }

        static std::string GetAssetPath()
        {
            return projectPath;
        }

    private:
        static inline std::string projectPath;
    };
}