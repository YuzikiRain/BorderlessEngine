#include "EditorWindow/Inspector.h"
#include "Selection.h"
#include "GameObject.h"
#include "imgui.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "FileUtility.h"
#include "yaml-cpp/yaml.h"
#include "Render/Model/Mesh.h"
#include "Render/Model/Model.h"
#include "Material.h"
#include <stdio.h>
#include "CustomPropertyDrawer/Vector3PropertyDrawer.h"
#include "CustomPropertyDrawer/ObjectPropertyDrawer.h"

namespace BorderlessEditor
{
	const unsigned int nameLimit = 30;
	Inspector::Inspector()
	{
		name = "Inspector";
		isOpen = false;
	}

	void Inspector::Draw()
	{
		if (Selection::current == NULL)
			return;
		BorderlessEngine::GameObject *obj = static_cast<BorderlessEngine::GameObject *>(Selection::current);

		// 右键添加组件
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Add Component"))
			{
				auto componentTypes = type::get<Component>().get_derived_classes();
				for (auto &componentType : componentTypes)
				{
					if (ImGui::MenuItem(componentType.get_name().to_string().c_str()))
					{
						obj->AddComponent(componentType.get_name().to_string());
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		ImGui::Checkbox("##isActive", &obj->isActive);
		// 横向布局
		ImGui::SameLine(0.0f, 10.0f);
		// 这里包括最后的\0空白符，所以需要加1
		ImGui::InputText("##name", (char *)obj->name.c_str(), nameLimit + 1);

		ImGui::NewLine();
		ImGui::Spacing();

		// 根据类型的字段类型自动绘制UI
		for (auto &kv : obj->components)
		{
			auto name = kv.first;
			ImGui::Text(name.c_str());
			auto componentPointer = kv.second;
			DrawComponent(componentPointer);
		}
	}

	void Inspector::DrawComponent(std::shared_ptr<Component> componentPointer)
	{
		auto type = type::get(*componentPointer);
		// 绘制所有字段
		for (auto &property : type.get_properties())
		{
			if (property.get_type() == type::get<glm::vec3>())
			{
				Vector3PropertyDrawer::Draw(property, componentPointer);
			}
			else
			{
				ObjectPropertyDrawer::Draw(property, componentPointer);
			}
		}
	}
}
