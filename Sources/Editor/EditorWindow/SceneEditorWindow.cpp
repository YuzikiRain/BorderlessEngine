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

		if (ImGui::IsWindowFocused())
		{
			if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))
				cameraTransform->position += cameraTransform->Front;
			if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))
				cameraTransform->position -= cameraTransform->Front;
			if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow))
				cameraTransform->position -= cameraTransform->Right;
			if (ImGui::IsKeyPressed(ImGuiKey_RightArrow))
				cameraTransform->position += cameraTransform->Right;

			/// @brief  按住鼠标右键拖拽Scene视角
			static float previousPitch = 0.0f;
			static float previousYaw = 0.0f;
			if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
			{
				auto delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
				cameraTransform->Yaw = previousYaw + delta.x;
				cameraTransform->Pitch = previousPitch - delta.y;

				glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

				// calculate the new Front vector
				glm::vec3 front;
				front.x = cos(glm::radians(cameraTransform->Yaw)) * cos(glm::radians(cameraTransform->Pitch));
				front.y = sin(glm::radians(cameraTransform->Pitch));
				front.z = sin(glm::radians(cameraTransform->Yaw)) * cos(glm::radians(cameraTransform->Pitch));
				cameraTransform->Front = glm::normalize(front);
				// also re-calculate the Right and Up vector
				cameraTransform->Right = glm::normalize(glm::cross(cameraTransform->Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
				cameraTransform->Up = glm::normalize(glm::cross(cameraTransform->Right, cameraTransform->Front));
			}
			else
			{
				previousYaw = cameraTransform->Yaw;
				previousPitch = cameraTransform->Pitch;
			}
			// ImGui::GetIO().WantCaptureMouse();
		}

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
