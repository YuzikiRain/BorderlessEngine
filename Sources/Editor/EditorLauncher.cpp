#include "EditorLauncher.h"
#include "Core/GLFWUtility.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "EditorWindow/EditorWindowManager.h"
#include "EditorSceneManager.h"
#include "ImguiManager.h"

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

#include "Render/MeshFilter.h"
#include "Render/Shader.h"

namespace BorderlessEditor
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    double targetFrameRate = 20.0;
    double realTime = 0.0;
    double frameTime = 0.0;
    double accumulator = 0.0;
    double timeScale = 1.0;
    double targetTime = 0.0;

    // static Shader defaultShader = Shader("F:/ForkSource/BorderlessEngine/Shader/unlit.vs", "F:/ForkSource/BorderlessEngine/Shader/unlit.fs");
    Shader defaultShader;

    double GetFrameInterval()
    {
        return 1.0 / targetFrameRate;
    }

    void EditorLauncher::Launch()
    {
        std::cout << "BorderlessEditor launched" << std::endl;

        BorderlessEngine::GLFWManager::Initialize(SCR_WIDTH, SCR_HEIGHT);
        auto glfwWindow = BorderlessEngine::GLFWManager::GetGLFWWindow();
        EditorWindowManager::Init();
        ImguiManager::InitImgui(glfwWindow);

        defaultShader = Shader("F:/ForkSource/BorderlessEngine/Shader/unlit.vs", "F:/ForkSource/BorderlessEngine/Shader/unlit.fs");
        Loop();

        ImguiManager::DestroyImgui();
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    void EditorLauncher::Loop()
    {
        auto glfwWindow = BorderlessEngine::GLFWManager::GetGLFWWindow();
        while (!glfwWindowShouldClose(glfwWindow))
        {
            // 输入
            Input();
            // 渲染
            Render();
            // 绘制编辑器UI
            ImguiManager::DrawImgui();
            // 交换缓冲区
            glfwSwapBuffers(glfwWindow);
            // 剩余的时间进行线程休眠，不进行多余的计算
            WaitForNextFrame();
        }
    }

    void EditorLauncher::Input()
    {
        // glfw提供的输入
        glfwPollEvents();
        // processInput(window);
    }

    void EditorLauncher::Render()
    {
        // 开启深度测试
        glEnable(GL_DEPTH_TEST);
        //// 开启剔除
        // glEnable(GL_CULL_FACE);
        //// 开启背面剔除
        // glCullFace(GL_BACK);
        //  线框模式
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        auto scene = EditorSceneManager::GetCurrentScene();
        if (scene != NULL)
        {
            auto gameObjects = scene->GetAllGameObjects();
            if (!gameObjects.empty() && gameObjects.size() > 0)
            {
                for (vector<BorderlessEngine::GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
                {
                    BorderlessEngine::GameObject *obj = (*it);
                    auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilter>();
                    if (meshFilter != NULL)
                    {
                        meshFilter->Model->Draw(defaultShader);
                    }
                }
            }
        }

        // 清屏
        glClearColor(0, 0, .7, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void EditorLauncher::WaitForNextFrame()
    {
        double currentTime = glfwGetTime();
        if (currentTime < targetTime)
            return;
        frameTime = currentTime - realTime;
        realTime = currentTime;

        // accumulator += frameTime;
        //// 模拟时间间隔，剩余的未模拟时间会累计到下一帧
        // while (accumulator < currentTime)
        //{
        //	InputSystem::FixedUpdate();
        //	accumulator += interval;
        // }

        targetTime += GetFrameInterval();
        // 休眠剩余到下一次Update的时间
        if (currentTime < targetTime)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((long)((targetTime - currentTime) * 1000)));
        }
    }

}