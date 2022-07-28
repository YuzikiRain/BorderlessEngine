#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace BorderlessEditor
{
    class EditorLauncher
    {
    public:
        static void Launch();
        static GLFWwindow *GetGLFWWindow();

    private:
        static GLFWwindow *glfwWindow;
        static bool InitializeWindow();
        static void Loop();
        static void Input();
        static void Render();
        static void InitImgui(GLFWwindow *window);
        static void DrawImgui();
        static void DestroyImgui();
        static void WaitForNextFrame();
    };
}