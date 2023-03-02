#pragma once
#include "EditorWindow/EditorWindow.h"
#include "imgui/imgui.h"
#include "DropManager.h"
#include "AssetDatabase.h"
#include "Core/GLFWManager.h"
#include <filesystem>
#include <string>

namespace BorderlessEditor
{
    class AssetBrowser : public EditorWindow
    {
    public:
        AssetBrowser()
        {
            name = "AssetBrowser";
            isOpen = false;
        }
        ~AssetBrowser()
        {
            Close();
        }

        void Open()
        {
            isOpen = true;
            assetPath = AssetDatabase::GetAssetPath();
            currentDirectory = std::filesystem::path(assetPath);

            OleInitialize(NULL);
            dropManager = DropManager();
            hwnd = GLFWManager::GetWin32Window();
            RegisterDragDrop(hwnd, &dropManager);
        }

        void Draw()
        {
            ImGui::Begin("AssetBrowser");

            // 拖拽
            // Using a Child allow to fill all the space of the window.
            // It also alows customization
            ImGui::BeginChild("AssetBrowser");
            // Get the size of the child (i.e. the whole draw size of the windows).

            if (dropManager.IsDragging()) // somehow set to true when dragging files on top of your application
            {
                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern)) // we use an external source (i.e. not ImGui-created)
                {
                    // replace "FILES" with whatever identifier you want - possibly dependant upon what type of files are being dragged
                    // you can specify a payload here with parameter 2 and the sizeof(parameter) for parameter 3.
                    // I store the payload within a vector of strings within the application itself so don't need it.
                    ImGui::SetDragDropPayload("FILES", nullptr, 0);
                    ImGui::BeginTooltip();
                    ImGui::Text("FILES");
                    ImGui::EndTooltip();
                    ImGui::EndDragDropSource();
                }
            }

            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("FILES"))
                {
                    auto d = payload->Data;
                }
            }

            // // Because I use the texture from OpenGL, I need to invert the V from the UV.
            // ImGui::Image((ImTextureID)texture, wsize, ImVec2(0, 1), ImVec2(1, 0));

            ImGui::EndChild();

            static float padding = 16;
            static float thumbnailSize = 128;
            float cellSize = thumbnailSize + padding;

            float panelWidth = ImGui::GetContentRegionAvail().x;
            int columnCount = panelWidth / cellSize;

            ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 128);
            ImGui::SliderFloat("padding", &padding, 0, 32);

            auto relativePath = std::filesystem::relative(currentDirectory, std::filesystem::path(assetPath).parent_path());
            ImGui::Text(relativePath.string().c_str());
            // 不是资源目录（根目录），则显示回到上一级按钮
            if (currentDirectory != std::filesystem::path(assetPath))
            {
                if (ImGui::Button("<-"))
                    currentDirectory = currentDirectory.parent_path();
            }

            // 显示当前目录
            ImGui::Columns(columnCount, 0, false);
            for (auto &directoryEntry : std::filesystem::directory_iterator(currentDirectory))
            {
                const auto &path = directoryEntry.path();
                auto relativePath = std::filesystem::relative(path, assetPath);
                string filenameString = relativePath.filename().string();

                ImGui::Button(directoryEntry.is_directory() ? "directory" : "file", {thumbnailSize, thumbnailSize});
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    if (directoryEntry.is_directory())
                        currentDirectory /= path.filename();
                }
                ImGui::Text(filenameString.c_str());

                ImGui::NextColumn();
            }

            ImGui::Columns(1);

            ImGui::End();
        }

        void Close()
        {
            RevokeDragDrop(hwnd);
            OleUninitialize();
            isOpen = false;
        }

    private:
        HWND hwnd;
        DropManager dropManager;
        std::string assetPath;
        std::filesystem::path currentDirectory;
    };
}