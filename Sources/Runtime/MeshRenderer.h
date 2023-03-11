#pragma once
#include "Render/Model/Mesh.h"
#include "Component.h"

namespace BorderlessEngine
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() : Component()
		{
			// mesh = new Mesh();
		}
		void Draw();
		Mesh *mesh ;
	};
}