#pragma once
#include "Model/Mesh.h"
#include "Component.h"
#include "Model/Model.h"

namespace BorderlessEngine
{
	class MeshFilter : public Component
	{
	public:
		MeshFilter() {}
		Mesh *Mesh;
		Model *Model;
	};
}