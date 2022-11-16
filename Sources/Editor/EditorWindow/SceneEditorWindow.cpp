#include "EditorWindow/SceneEditorWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "Scene.h"
#include "EditorSceneManager.h"
#include "Render/MeshRenderer.h"
#include "Transform.h"

namespace BorderlessEditor
{
	SceneEditorWindow::SceneEditorWindow()
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

		this->cameraGameObject = new BorderlessEngine::GameObject("sceneCamera");
		this->cameraGameObject->AddComponent<BorderlessEngine::Transform>();
	}

	void SceneEditorWindow::Draw()
	{
		// 渲染到帧缓冲（附件为纹理）
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto transform = this->cameraGameObject->GetComponent<BorderlessEngine::Transform>();
		auto position = transform->position;
		// 绘制一些东西
		auto objs = EditorSceneManager::GetAllGameObjects();
		for (vector<BorderlessEngine::GameObject *>::iterator it = objs.begin(); it != objs.end(); it++)
		{
			// 迭代器it是指向BorderlessEngine::GameObject *的指针
			BorderlessEngine::GameObject* obj = *(it);
			auto meshRenderer = obj->GetComponent<BorderlessEngine::MeshRenderer>();
		}

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

	// void SceneEditorWindow::Dispose()
	// {
	// 	glDeleteFramebuffers(1, &fbo);
	// }

}
