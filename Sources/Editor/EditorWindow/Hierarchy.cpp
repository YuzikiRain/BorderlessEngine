#include "EditorWindow/Hierarchy.h"
#include "EditorSceneManager.h"
#include "imgui/imgui.h"
#include "Selection.h"

namespace BorderlessEditor
{
	Hierarchy::Hierarchy()
	{
		name = "Hierarchy";
		isOpen = false;
	}
	void Hierarchy::Draw()
	{
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("GameObject"))
				{
					BorderlessEditor::EditorSceneManager::CreateNewGameObject();
				}
				if (ImGui::MenuItem("Test GameObject"))
				{
					BorderlessEditor::EditorSceneManager::CreateNewCube();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		auto objs = BorderlessEditor::EditorSceneManager::GetAllGameObjects();
		for (size_t i = 0; i < objs.size(); i++)
		{
			auto obj = objs[i];
			ImGuiTreeNodeFlags node_flags = base_flags;
			if (BorderlessEditor::Selection::current == obj)
				node_flags |= ImGuiTreeNodeFlags_Selected;
			bool node_open = ImGui::TreeNodeEx((void *)(intptr_t)i, node_flags, obj->name.c_str());
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				BorderlessEditor::Selection::current = obj;
			}
			if (node_open)
			{
				ImGui::TreePop();
			}
		}

		if (ImGui::TreeNode("Basic trees"))
		{
			for (int i = 0; i < 5; i++)
			{
				// Use SetNextItemOpen() so set the default state of a node to be open. We could
				// also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
				if (i == 0)
					ImGui::SetNextItemOpen(true, ImGuiCond_Once);

				if (ImGui::TreeNode((void *)(intptr_t)i, "Child %d", i))
				{
					// Selection::current = ;
					if (ImGui::BeginPopupContextItem())
					{
						ImGui::Text("Edit name:");
						// ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
						if (ImGui::Button("Close"))
							ImGui::CloseCurrentPopup();
						ImGui::EndPopup();
					}
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}
}
