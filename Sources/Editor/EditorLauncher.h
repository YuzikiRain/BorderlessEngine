#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace BorderlessEditor
{
    class EditorLauncher
    {
    public:
        static void Launch();
    private:
        static GLFWwindow *window;
        static bool InitializeWindow();
        static void Loop();
        static void InitImgui(GLFWwindow *window);
        static void DrawImgui();
        static void DestroyImgui();
    };
}