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

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

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