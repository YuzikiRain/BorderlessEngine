#pragma once

#include <string>
#include "yaml-cpp/yaml.h"

namespace BorderlessEditor
{
    class AssetDatabase
    {
    public:
        template <typename T>
        static T LoadAssetAtPath<T>(std::string path)
        {
            
        }

    private:
        // static Scene *currentScene;
    };
}