#pragma once
#include "Scene.h"
#include <fstream>
#include <shobjidl.h>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using Scene = BorderlessEngine::Scene;

namespace BorderlessEditor
{
    class EditorSceneManager
    {
    public:
        static std::string LoadFile(const char *filter);
        static std::string SaveFile(const char *filter);
        static void NewScene();
        static void OpenScene();
        static void SaveScene();
        static void CloseScene();
        static void CreateNewGameObject();
        static vector<BorderlessEngine::GameObject *> GetAllGameObjects();

    private:
        static Scene *currentScene;
    };
}