#pragma once
#include "Render/Model/Mesh.h"
#include "Component.h"
#include "Render/Model/Model.h"
#include "Render/Model/MyMesh.h"

namespace BorderlessEngine
{
	class MeshFilter : public Component
	{
	public:
		MeshFilter() {}
		MyMesh Mesh;
		Model *Model;

        YAML::Node Serialize() override {
            YAML::Node node;
            node["mesh"] = "ttt";
            return node;
        }

	private:
		;

		RTTR_ENABLE(Component)
	};
}