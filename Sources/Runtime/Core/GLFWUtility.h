#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace BorderlessEngine
{
    class GLFWManager
    {
    public:
        static bool Initialize(unsigned int width, unsigned int height);
        static GLFWwindow *GetGLFWWindow();
        static HWND GetWin32Window();

    private:
        static GLFWwindow *glfwWindow;
    };
}