#include "EditorWindow/GameEditorWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "Scene.h"
#include "EditorSceneManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "Material.h"

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
        // 开启深度测试
        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImVec2 wsize = ImGui::GetWindowSize();

        // 绘制一些东西
        auto objs = EditorSceneManager::GetAllGameObjects();
        for (vector<BorderlessEngine::GameObject *>::iterator it = objs.begin(); it != objs.end(); it++)
        {
            auto obj = *it;
            auto transform = obj->GetComponent<BorderlessEngine::Transform>();
            auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilter>();
            auto material = *obj->GetComponent<BorderlessEngine::Material>();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform->Position);
            material.shader->setMatrix4("model", model);
            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            // glm::mat4 view = glm::lookAt(transform->Position, transform->Position + transform->Front, transform->Up);
            material.shader->setMatrix4("view", view);
            glm::mat4 projection = glm::perspective(glm::radians(60.0f), wsize.x / wsize.y, 0.1f, 100.0f);
            material.shader->setMatrix4("projection", projection);

            material.shader->use();
            meshFilter->Model->Draw(*material.shader);

            // obj.GetComponent<MeshRenderer>();
            // w.BeginDraw();
            // if (w.isOpen)
            // 	w.Draw();
            // w.EndDraw();
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Using a Child allow to fill all the space of the window.
        // It also alows customization
        ImGui::BeginChild("GameRender");
        // Get the size of the child (i.e. the whole draw size of the windows).

        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image((ImTextureID)texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }

    // void GameEditorWindow::Dispose()
    // {
    // 	glDeleteFramebuffers(1, &fbo);
    // }

}
