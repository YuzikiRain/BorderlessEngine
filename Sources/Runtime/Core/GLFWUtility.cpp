#include "Core/GLFWUtility.h"
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace BorderlessEngine
{
    GLFWwindow *GLFWManager::glfwWindow = 0;

    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool GLFWManager::Initialize(unsigned int width, unsigned int height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
        if (glfwWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(glfwWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glViewport(0, 0, width, height);

        glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);

        return 0;
    }

    GLFWwindow *GLFWManager::GetGLFWWindow()
    {
        return GLFWManager::glfwWindow;
    }

    HWND GLFWManager::GetWin32Window()
    {
        return glfwGetWin32Window(GetGLFWWindow());
    }

}