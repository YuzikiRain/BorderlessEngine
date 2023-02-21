#pragma once
#include "Model/Mesh.h"
#include "Component.h"
#include "Model/Model.h"
#include "Model/MyMesh.h"

namespace BorderlessEngine
{
	class MeshFilter : public Component
	{
	public:
		MeshFilter() {}
		MyMesh *Mesh;
		Model *Model;
	};
}