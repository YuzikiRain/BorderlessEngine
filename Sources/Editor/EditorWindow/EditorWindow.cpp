#include <EditorWindow/EditorWindow.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl2.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

namespace BorderlessEditor
{
	void EditorWindow::Open()
	{
		isOpen = true;
	}
	void EditorWindow::BeginDraw()
	{
		ImGui::Begin(name, &isOpen, ImGuiWindowFlags_None);
	}
	void EditorWindow::Draw()
	{
	}
	void EditorWindow::EndDraw()
	{
		ImGui::End();
	}
	const char *name = "EditorWindow";
	bool isOpen = false;
}