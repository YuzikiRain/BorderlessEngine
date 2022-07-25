#include "EditorSceneManager.h"
#include "Scene.h"
#include <fstream>
// yaml-cpp
#include "yaml-cpp/yaml.h"
#include <shobjidl.h>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
// 打开文件对话框
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "EditorLauncher.h"

using Scene = BorderlessEngine::Scene;

namespace BorderlessEditor
{
    const char *sceneFilter = "Scene (*.scene)\0*.scene\0";
    const char *sceneFileExtension = "scene";
    Scene *EditorSceneManager::currentScene;

    std::string EditorSceneManager::LoadFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(EditorLauncher::GetGLFWWindow());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        else
            return std::string();
    }

    std::string EditorSceneManager::SaveFile(const char *filter)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(EditorLauncher::GetGLFWWindow());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrDefExt = sceneFileExtension;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        else
            return std::string();
    }

    void EditorSceneManager::NewScene()
    {
        CloseScene();
        currentScene = new BorderlessEngine::Scene();
    }

    void EditorSceneManager::OpenScene()
    {
        auto path = LoadFile(sceneFilter);
        if (path.empty())
            return;

        CloseScene();

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

    void EditorSceneManager::SaveScene()
    {
        auto path = SaveFile(sceneFilter);
        if (path.empty())
            return;

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

    void EditorSceneManager::CloseScene()
    {
        delete currentScene;
    }

    void EditorSceneManager::CreateNewGameObject()
    {
        currentScene->AddEmptyGameObject();
    }

    vector<BorderlessEngine::GameObject *> EditorSceneManager::GetAllGameObjects()
    {
        return currentScene->GetAllGameObjects();
    }
}