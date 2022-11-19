#include "EditorWindow/SceneEditorWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "Scene.h"
#include "EditorSceneManager.h"
#include "Transform.h"
#include "Render/MeshRenderer.h"
#include "Render/MeshFilter.h"
#include "Render/Material.h"
#include "Render/Camera.h"

namespace BorderlessEditor
{
	SceneEditorWindow::SceneEditorWindow()
	{
		name = "Scene";
		isOpen = false;

		// 创建帧缓冲
		glGenFramebuffers(1, &fbo);
		// 创建帧缓冲的纹理附件
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		cameraGameObject = new BorderlessEngine::GameObject("SceneCamera");
		auto cameraTransform = cameraGameObject->AddComponent<BorderlessEngine::Transform>();
		cameraTransform->position = glm::vec3(0.0f, 0.0f, 10.0f);
		cameraTransform->Front = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraTransform->Up = glm::vec3(0.0f, 1.0f, 0.0f);
		auto camera = cameraGameObject->AddComponent<BorderlessEngine::Camera>();
		camera->fov = 60.0f;
		camera->nearPlane = 0.01f;
		camera->farPlane = 100.0f;
	}

	void SceneEditorWindow::Draw()
	{
		// 渲染到帧缓冲（附件为纹理）
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		// 开启深度测试
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImVec2 wsize = ImGui::GetWindowSize();

		auto cameraTransform = cameraGameObject->GetComponent<BorderlessEngine::Transform>();
		auto camera = cameraGameObject->GetComponent<BorderlessEngine::Camera>();

		if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))
			cameraTransform->position += cameraTransform->Front;
		if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))
			cameraTransform->position -= cameraTransform->Front;
		if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow))
			cameraTransform->position -= cameraTransform->Right;
		if (ImGui::IsKeyPressed(ImGuiKey_RightArrow))
			cameraTransform->position += cameraTransform->Right;

		// 绘制一些东西
		auto objs = EditorSceneManager::GetAllGameObjects();
		for (vector<BorderlessEngine::GameObject *>::iterator it = objs.begin(); it != objs.end(); it++)
		{
			auto obj = *it;
			auto transform = obj->GetComponent<BorderlessEngine::Transform>();
			auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilter>();
			auto material = *obj->GetComponent<BorderlessEngine::Material>();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform->position);
			material.shader->setMatrix4("model", model);
			glm::mat4 view = glm::lookAt(cameraTransform->position, cameraTransform->position + cameraTransform->Front * 10.0f, cameraTransform->Up);
			material.shader->setMatrix4("view", view);
			glm::mat4 projection = glm::perspective(glm::radians(camera->fov), wsize.x / wsize.y, camera->nearPlane, camera->farPlane);
			material.shader->setMatrix4("projection", projection);

			material.shader->use();
			meshFilter->Model->Draw(*material.shader);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::BeginChild("SceneRender");
		// Get the size of the child (i.e. the whole draw size of the windows).

		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}

}
