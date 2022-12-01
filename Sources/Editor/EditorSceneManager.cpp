#include "EditorSceneManager.h"
#include "Scene.h"
#include <fstream>
// yaml-cpp
#include "yaml-cpp/yaml.h"
#include <shobjidl.h>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "EditorLauncher.h"
#include "FileUtility.h"
#include "Transform.h"

using Scene = BorderlessEngine::Scene;

namespace BorderlessEditor
{
    const char *sceneFilter = "Scene (*.scene)\0*.scene\0";
    const char *sceneFileExtension = "scene";
    Scene *EditorSceneManager::currentScene;

    void EditorSceneManager::NewScene()
    {
        CloseScene();
        currentScene = new BorderlessEngine::Scene();
    }

    void EditorSceneManager::OpenScene()
    {
        auto path = FileUtility::OpenFileDialogue(sceneFilter, sceneFileExtension);
        if (path.empty())
            return;

        CloseScene();

        YAML::Node sceneData = YAML::LoadFile(path);
        auto objs = vector<BorderlessEngine::GameObject *>();

        for (size_t i = 0; i < sceneData["gameObjects"].size(); i++)
        {
            auto name = sceneData["gameObjects"][i]["name"].as<string>();
            auto obj = new BorderlessEngine::GameObject(name.c_str(), sceneData["gameObjects"][i]["isActive"].as<bool>());
            auto transform = obj->AddComponent<BorderlessEngine::Transform>();
            objs.push_back(obj);
        }
        currentScene = new BorderlessEngine::Scene("scene", objs);
    }

    void EditorSceneManager::SaveScene()
    {
        auto path = FileUtility::SaveFileDialogue(sceneFilter, sceneFileExtension);
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

    Scene *EditorSceneManager::GetCurrentScene()
    {
        return currentScene;
    }

    void EditorSceneManager::CreateNewGameObject()
    {
        currentScene->AddEmptyGameObject();
    }

    void EditorSceneManager::CreateNewCube()
    {
        currentScene->AddCube();
    }

    vector<BorderlessEngine::GameObject *> EditorSceneManager::GetAllGameObjects()
    {
        return currentScene->GetAllGameObjects();
    }
}