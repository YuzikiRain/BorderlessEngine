#pragma once
#include "Scene.h"
#include <fstream>
#include "yaml-cpp/yaml.h"
#include <shobjidl.h>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

using Scene = BorderlessEngine::Scene;

namespace BorderlessEditor
{
    class EditorSceneManager
    {
    public:
        static std::string LoadFile()
        {
            OPENFILENAMEA ofn;
            CHAR szFile[260] = {0};
            ZeroMemory(&ofn, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.lpstrFile = szFile;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetOpenFileNameA(&ofn) == TRUE)
                return ofn.lpstrFile;
            else
                return std::string();
        }

        static std::string SaveFile()
        {
            OPENFILENAMEA ofn;
            CHAR szFile[260] = {0};
            ZeroMemory(&ofn, sizeof(OPENFILENAME));
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.lpstrFile = szFile;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetSaveFileNameA(&ofn) == TRUE)
                return ofn.lpstrFile;
            else
                return std::string();
        }

        static void NewScene()
        {
            CloseScene();
            currentScene = new BorderlessEngine::Scene();
        }

        static void OpenScene()
        {
            auto path = LoadFile();
            if (path.empty())
                return;

            CloseScene();

            // char pathBuffer[255];
            // WideCharToMultiByte(CP_ACP, 0, path, -1, pathBuffer, sizeof(pathBuffer), NULL, NULL);

            YAML::Node sceneData = YAML::LoadFile(path);
            auto objs = vector<BorderlessEngine::GameObject *>();

            for (size_t i = 0; i < sceneData["gameObjects"].size(); i++)
            {
                auto name = sceneData["gameObjects"][i]["name"].as<string>();
                objs.push_back(
                    new BorderlessEngine::GameObject(
                        name.c_str(),
                        sceneData["gameObjects"][i]["isActive"].as<bool>()));
            }
            currentScene = new BorderlessEngine::Scene("scene", objs);
        }

        static void SaveScene()
        {
            // auto path = static_cast<std::string>(SaveFile());
            auto path = SaveFile();
            if (path.empty())
                return;

            // char pathBuffer[255];
            // WideCharToMultiByte(CP_ACP, 0, path, -1, pathBuffer, sizeof(pathBuffer), NULL, NULL);

            fstream sceneFileStream;
            sceneFileStream.open(path, ios::out | ios::trunc);
            YAML::Node scene;
            auto objs = currentScene->GetAllGameObjects();
            for (size_t i = 0; i < objs.size(); i++)
            {
                auto obj = objs[i];
                scene["gameObjects"][i]["name"] = obj->name;
                scene["gameObjects"][i]["isActive"] = obj->isActive;
            }

            sceneFileStream << scene;
            sceneFileStream.close();
        }

        static void CloseScene()
        {
            delete currentScene;
        }

        static void CreateNewGameObject()
        {
            currentScene->AddEmptyGameObject();
        }

        static vector<BorderlessEngine::GameObject *> GetAllGameObjects()
        {
            return currentScene->GetAllGameObjects();
        }

    private:
        static Scene *currentScene;
    };
}