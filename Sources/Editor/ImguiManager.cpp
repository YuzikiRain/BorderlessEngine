#include "ImguiManager.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "EditorWindow/EditorWindowManager.h"
#include "EditorSceneManager.h"

namespace BorderlessEditor
{
    void ImguiManager::InitImgui(GLFWwindow *window)
    {
        ImGui::CreateContext();                     // Setup Dear ImGui context
        ImGui::StyleColorsDark();                   // Setup Dear ImGui style
        ImGui_ImplGlfw_InitForOpenGL(window, true); // Setup Platform/Renderer backends
        ImGui_ImplOpenGL3_Init("#version 450");

        // 启用docking
        ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_DockingEnable;
    }

    void ImguiManager::DrawImgui()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        bool isFrameRateOpen = false;
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

        auto editorWindows = *EditorWindowManager::GetAllEditorwindows();
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
            if (ImGui::BeginMenu("Window"))
            {
                for (size_t i = 0; i < editorWindows.size(); i++)
                {
                    EditorWindow &editorWindow = *(editorWindows[i]);
                    if (ImGui::MenuItem(editorWindow.name))
                    {
                        editorWindow.Open();
                    }
                }

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // 更新所有window
        for (size_t i = 0; i < editorWindows.size(); i++)
        {
            EditorWindow &editorWindow = *(editorWindows[i]);
            if (editorWindow.isOpen)
            {
                editorWindow.BeginDraw();
                editorWindow.Draw();
                editorWindow.EndDraw();
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

    void ImguiManager::DestroyImgui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}