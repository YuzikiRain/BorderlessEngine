#include "EditorWindow/Inspector.h"
#include "Selection.h"
#include "GameObject.h"
#include "imgui.h"
#include "Render/MeshFilter.h"
#include "Render/MeshRenderer.h"
#include "FileUtility.h"
#include "yaml-cpp/yaml.h"
#include "Render/Model/Mesh.h"
#include "Render/Model/Model.h"
#include "Render/Material.h"
#include <stdio.h>
#include "Render/Camera.h"
#include "Transform.h"
#include "CustomPropertyDrawer/Vector3PropertyDrawer.h"

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
				if (ImGui::MenuItem("Transform"))
				{
					obj->AddComponent<BorderlessEngine::Transform>();
				}
				if (ImGui::MenuItem("MeshFilter"))
				{
					const char *sceneFilter = "obj (*.obj)\0*.obj\0";
					const char *sceneFileExtension = "obj";
					auto path = FileUtility::OpenFileDialogue(sceneFilter, sceneFileExtension);
					if (path.empty())
						return;

					BorderlessEngine::MeshFilter *meshFilter = obj->AddComponent<BorderlessEngine::MeshFilter>();
					meshFilter->Model = new BorderlessEngine::Model(path);
					printf(meshFilter->Model->Name.c_str());
				}
				if (ImGui::MenuItem("MeshRenderer"))
				{
					obj->AddComponent<BorderlessEngine::MeshRenderer>();
				}
				if (ImGui::MenuItem("Camera"))
				{
					obj->AddComponent<BorderlessEngine::Camera>();
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

		for (auto &kv : obj->components)
		{
			auto name = kv.first;
			ImGui::Text(name.c_str());
			auto componentPointer = kv.second;
			DrawComponent(componentPointer);
		}

		// // 绘制物体的组件，TODO:实现反射，根据类型的字段类型自动绘制UI
		// auto transform = obj->GetComponent<BorderlessEngine::Transform>();
		// if (transform != NULL)
		// {
		// 	// 遍历成员函数(Method)、成员变量(Property)
		// 	{
		// 		type t = type::get<BorderlessEngine::Transform>();
		// 		for (auto &prop : t.get_properties())
		// 		{
		// 			ImGui::Text(prop.get_name().to_string().c_str());
		// 			if (prop.get_type() == type::get<glm::vec3>())
		// 			{
		// 				variant var_prop = prop.get_value(transform);
		// 				float f3[3] = {transform->Position.x, transform->Position.y, transform->Position.z};
		// 				ImGui::InputFloat3("Position", f3);
		// 				transform->Position.x = f3[0];
		// 				transform->Position.y = f3[1];
		// 				transform->Position.z = f3[2];
		// 			}
		// 			std::cout << "name: " << prop.get_name() << std::endl;
		// 		}

		// 		for (auto &meth : t.get_methods())
		// 			std::cout << "name: " << meth.get_name() << std::endl;
		// 	}
		// 	ImGui::Text("Transform");
		// 	float f3[3] = {transform->Position.x, transform->Position.y, transform->Position.z};
		// 	ImGui::InputFloat3("Position", f3);
		// 	transform->Position.x = f3[0];
		// 	transform->Position.y = f3[1];
		// 	transform->Position.z = f3[2];
		// }

		auto meshFilter = obj->GetComponent<BorderlessEngine::MeshFilter>();
		if (meshFilter != NULL)
		{
			ImGui::Text("MeshFilter");
			ImGui::LabelText("MeshFilter.Reference", meshFilter->Model != NULL ? meshFilter->Model->Path.c_str() : "null");
			// auto a = meshFilter->Mesh->Name;
			// ImGui::LabelText("MeshFilter.Reference", meshFilter->Mesh != NULL ? meshFilter->Mesh->Path.c_str() : "null");
			if (ImGui::Button("set"))
			{
				const char *sceneFilter = "Mesh (*.mesh)\0*.mesh\0";
				const char *sceneFileExtension = "mesh";
				string path = FileUtility::OpenFileDialogue(sceneFilter, sceneFileExtension);
				if (!path.empty())
				{
					// YAML::Node data = YAML::LoadFile(path);
					// BorderlessEngine::Mesh *mesh = new BorderlessEngine::Mesh();
					// mesh.
					// for (size_t i = 0; i < data["gameObjects"].size(); i++)
					// {
					// 	auto name = data["gameObjects"][i]["name"].as<string>();
					// 	objs.push_back(
					// 		new BorderlessEngine::GameObject(
					// 			name.c_str(),
					// 			data["gameObjects"][i]["isActive"].as<bool>()));
					// }
					// currentScene = new BorderlessEngine::Scene("scene", objs);
				}
			}
		}
		auto material = obj->GetComponent<BorderlessEngine::Material>();
		if (ImGui::Button("Set Vertex Shader"))
		{
			const char *shaderFilter = "Shader (*.mesh)\0*.mesh\0";
			const char *shaderFileExtension = "vs";
			string path = FileUtility::OpenFileDialogue(shaderFilter, shaderFileExtension);
			if (!path.empty())
			{
				YAML::Node data = YAML::LoadFile(path);
				material->shader->ChangeVertex(path.c_str());
			}
		}
		if (ImGui::Button("Set Fragment Shader"))
		{
			const char *shaderFilter = "Shader (*.fs)\0*.fs\0";
			const char *shaderFileExtension = "fs";
			string path = FileUtility::OpenFileDialogue(shaderFilter, shaderFileExtension);
			if (!path.empty())
			{
				YAML::Node data = YAML::LoadFile(path);
				material->shader->ChangeFragment(path.c_str());
			}
		}
		if (ImGui::Button("Edit"))
		{
		}
	}

	void Inspector::DrawComponent(Component *componentPointer)
	{
		auto type = type::get(*componentPointer);
		// 绘制所有字段
		for (auto &property : type.get_properties())
		{
			if (property.get_type() == type::get<glm::vec3>())
			{
				Vector3PropertyDrawer::Draw(property, componentPointer);
			}
		}
	}
}
