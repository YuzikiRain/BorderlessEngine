#pragma once
#include "Render/Model/Mesh.h"
#include "Component.h"

namespace BorderlessEngine
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		void Draw();

	// private:
		Mesh *mesh = 0;
		// Mesh mesh;
	};
}