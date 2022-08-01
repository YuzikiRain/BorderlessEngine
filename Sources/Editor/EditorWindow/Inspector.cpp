#include "EditorWindow/Inspector.h"
#include "Selection.h"
#include "GameObject.h"
#include "imgui.h"
#include "Render/MeshFilter.h"
#include "Render/MeshRenderer.h"
#include "FileUtility.h"
#include "yaml-cpp/yaml.h"

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
				if (ImGui::MenuItem("MeshFilter"))
				{
					obj->AddComponent<BorderlessEngine::MeshFilter>();
				}
				if (ImGui::MenuItem("MeshRenderer"))
				{
					obj->AddComponent<BorderlessEngine::MeshRenderer>();
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

		// 绘制物体的组件，TODO:实现反射，根据类型的字段类型自动绘制UI
		auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilter>();
		if (meshFilter != NULL)
		{
			ImGui::Text("MeshFilter");
			auto a = meshFilter->Mesh->Name;
			ImGui::LabelText("MeshFilter.Reference", meshFilter->Mesh != NULL ? meshFilter->Mesh->Path.c_str() : "null");
			if (ImGui::Button("set"))
			{
				const char *sceneFilter = "Mesh (*.mesh)\0*.mesh\0";
				const char *sceneFileExtension = "mesh";
				string path = FileUtility::OpenFileDialogue(sceneFilter, sceneFileExtension);
				if (!path.empty())
				{
					YAML::Node data = YAML::LoadFile(path);
					Mesh mesh = new Mesh();
					auto objs = vector<BorderlessEngine::GameObject *>();

					for (size_t i = 0; i < data["gameObjects"].size(); i++)
					{
						auto name = data["gameObjects"][i]["name"].as<string>();
						objs.push_back(
							new BorderlessEngine::GameObject(
								name.c_str(),
								data["gameObjects"][i]["isActive"].as<bool>()));
					}
					currentScene = new BorderlessEngine::Scene("scene", objs);
				}
			}
		}
	}
}
