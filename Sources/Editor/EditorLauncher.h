#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "EditorWindow/EditorWindowManager.h"
#include "EditorSceneManager.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // glViewport(0, 0, width, height);
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

double targetFrameRate = 20.0;
double realTime = 0.0;
double frameTime = 0.0;
double accumulator = 0.0;
double timeScale = 1.0;
double targetTime = 0.0;

namespace BorderlessEditor
{
    class EditorLauncher
    {
    public:
        static void Launch()
        {
            std::cout << "BorderlessEditor launched" << std::endl;
            InitializeWindow();
            InitImgui(window);

            Loop();

            DestroyImgui();
        }

    private:
        static GLFWwindow *window;
        static bool InitializeWindow()
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
            if (window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }

            glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            return 0;
        }

        static void Loop()
        {
            while (!glfwWindowShouldClose(window))
            {
                DrawImgui();

                // 开启深度测试
                glEnable(GL_DEPTH_TEST);
                //// 开启剔除
                // glEnable(GL_CULL_FACE);
                //// 开启背面剔除
                // glCullFace(GL_BACK);
                //  线框模式
                // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                glClearColor(0, 0, .4, 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glfwSwapBuffers(window);
            }
        }

        static void InitImgui(GLFWwindow *window)
        {
            ImGui::CreateContext();                     // Setup Dear ImGui context
            ImGui::StyleColorsDark();                   // Setup Dear ImGui style
            ImGui_ImplGlfw_InitForOpenGL(window, true); // Setup Platform/Renderer backends
            ImGui_ImplOpenGL3_Init("#version 450");

            bool show_demo_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            // 启用docking
            ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
        }

        static void DrawImgui()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            static bool isFrameRateOpen = false;
            ImGuiWindowFlags window_flags =
                // ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoDecoration |     // 不需要标题、不需要调整大小、不需要滚动条、不需要折叠
                ImGuiWindowFlags_AlwaysAutoResize | // 自动调整大小
                // ImGuiWindowFlags_NoSavedSettings |				// 不需要保存加载布局信息
                ImGuiWindowFlags_NoFocusOnAppearing | // 显示时不需要获取交点
                ImGuiWindowFlags_NoNav;
            // if (ImGui::Begin("frame rate", &isFrameRateOpen, window_flags))
            // {
            //     ImGui::InputDouble("targetFrameRate", &BorderlessEditor::targetFrameRate, 1.0f, 5.0f, "%.2f");
            //     ImGui::Text("frame rate %.0lf", BorderlessEngine::GetFrameRate());
            //     ImGui::End();
            // }

            auto windows = EditorWindowManager::GetAllEditorwindows();

            // 主菜单
            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("New Scene"))
                    {
                        BorderlessEditor::EditorSceneManager::NewScene();
                    }
                    if (ImGui::MenuItem("Open Scene"))
                    {
                        BorderlessEditor::EditorSceneManager::OpenScene();
                    }
                    if (ImGui::MenuItem("Save Scene"))
                    {
                        BorderlessEditor::EditorSceneManager::SaveScene();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("EditorWindow"))
                {
                    for (size_t i = 0; i < windows.size(); i++)
                    {
                        EditorWindow &window = (*windows[i]);
                        if (ImGui::MenuItem(window.name))
                        {
                            window.Open();
                        }
                    }

                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            // 更新所有window
            for (size_t i = 0; i < windows.size(); i++)
            {
                EditorWindow &window = (*windows[i]);
                if (window.isOpen)
                {
                    window.BeginDraw();
                    window.Draw();
                    window.EndDraw();
                }
            }

            // for (vector<EditorWindow*>::iterator it = windows.begin(); it != windows.end(); it++)
            //{
            //	EditorWindow* window;
            //	window = &(it);
            //	EditorWindow w = (*it);
            //	w.BeginDraw();
            //	if (w.isOpen)
            //		w.Draw();
            //	w.EndDraw();
            // }

            ImGui::ShowDemoWindow();

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        static void DestroyImgui()
        {
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    };
}