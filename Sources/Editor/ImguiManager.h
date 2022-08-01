#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace BorderlessEditor
{
    class ImguiManager
    {
    public:
        static void InitImgui(GLFWwindow *window);
        static void DrawImgui();
        static void DestroyImgui();
    };
}