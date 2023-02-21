#include "EditorLauncher.h"
#include "Core/GLFWUtility.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "EditorWindow/EditorWindowManager.h"
#include "EditorSceneManager.h"
#include "ImguiManager.h"
#include "Input/InputSystem.h"
#include "AssetExplorer.h"
#include <filesystem>

#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

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

    double GetFrameInterval()
    {
        return 1.0 / targetFrameRate;
    }

    void EditorLauncher::Launch()
    {
        std::cout << "BorderlessEditor launched" << std::endl;

        BorderlessEngine::GLFWManager::Initialize(SCR_WIDTH, SCR_HEIGHT);
        auto glfwWindow = BorderlessEngine::GLFWManager::GetGLFWWindow();

        // 初始化
        // AssetExplorer::StartWatching(std::filesystem::current_path());
        EditorWindowManager::Init();
        ImguiManager::InitImgui(glfwWindow);

        // 循环
        Loop();

        // 退出
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
            BorderlessEngine::InputSystem::Update(glfwWindow);
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

    void EditorLauncher::Input(GLFWwindow *window)
    {

    }

    void EditorLauncher::Render()
    {
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