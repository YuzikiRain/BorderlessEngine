#include "EditorWindow/Inspector.h"
#include "Selection.h"
#include "GameObject.h"
#include "imgui.h"
#include "Render/MeshFilterComponent.h"

namespace BorderlessEditor
{
	const unsigned int nameLimit = 30;
	Inspector::Inspector()
	{
		name = "Inspector";
	}

	void  Inspector::Draw()
	{
		if (Selection::current == NULL) return;
		BorderlessEngine::GameObject* obj = static_cast<BorderlessEngine::GameObject*>(Selection::current);

		// 右键添加组件
		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::BeginMenu("Add Component"))
			{
				if (ImGui::MenuItem("MeshFilter Component"))
				{
					obj->AddComponent<BorderlessEngine::MeshFilterComponent>();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}


		ImGui::Checkbox("##isActive", &obj->isActive);
		// 横向布局
		ImGui::SameLine(0.0f, 10.0f);
		// 这里包括最后的\0空白符，所以需要加1
		ImGui::InputText("##name", obj->name, nameLimit + 1);

		ImGui::NewLine();
		ImGui::Spacing();

		// 绘制物体的组件
		auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilterComponent>();
		if (meshFilter != NULL)
		{
			ImGui::Text("MeshFilter");
		}
	}
}
