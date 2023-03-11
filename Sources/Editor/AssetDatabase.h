#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshFilter.h"
#include <iostream>
#include <queue>
#include <fstream>

#include "TestJson.h"

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
            // std::fstream sceneFileStream;
            // sceneFileStream.open(path, std::ios::out | std::ios::trunc);
            // sceneFileStream << object->Serialize();
            // sceneFileStream.close();

            std::cout << object->Serialize();
        }

        static void ProcessGameObject(Transform &transform, YAML::Node &node, int count)
        {
            auto obj = transform.GetGameObject();
            YAML::Node g;
            g["name"] = obj->name;
            g["isActive"] = obj->isActive;
            // g[count]["id"] = obj->name;
            node["GameObjects"].push_back(g);

            YAML::Node t;
            t["index"] = transform.childIndex;
            node["Transforms"].push_back(t);
            // node["transform"][count]["gameObject"] = obj->childIndex;

            // auto meshFilter = obj->GetComponent<MeshFilter>();
            YAML::Node m;
            m = TestA();
            // m["name"] = obj->name;
            // m["mesh"] = meshFilter.Mesh;
            node["Meshes"].push_back(m);
            std::cout << m << std::endl;
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