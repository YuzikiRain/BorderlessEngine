#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace BorderlessEditor
{
    class EditorLauncher
    {
    public:
        static void Launch();

    private:
        static void Loop();
        static void Input();
        static void Render();
        static void WaitForNextFrame();
    };
}