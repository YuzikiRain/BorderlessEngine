#include "EditorWindow/GameEditorWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

namespace BorderlessEditor
{
	GameEditorWindow::GameEditorWindow()
	{
		name = "Game";
		isOpen = false;

		// 创建帧缓冲
		glGenFramebuffers(1, &fbo);
		// 创建帧缓冲的纹理附件
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void GameEditorWindow::Draw()
	{
		// 渲染到帧缓冲（附件为纹理）
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClearColor(0.6, 0, .4, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("GameRender");
		// Get the size of the child (i.e. the whole draw size of the windows).
		ImVec2 wsize = ImGui::GetWindowSize();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}

	// void GameEditorWindow::Dispose()
	// {
	// 	glDeleteFramebuffers(1, &fbo);
	// }

}
