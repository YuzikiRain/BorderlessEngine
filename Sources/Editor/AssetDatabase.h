#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include "GameObject.h"

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

        static void SaveAsset(Object object, string path)
        {
            if (typeid(object) == typeid(GameObject))
            {

            }
        }

    private:
        // static Scene *currentScene;
    };
}