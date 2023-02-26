#pragma once
#include "Component.h"
#include "Render/Shader.h"

namespace BorderlessEngine
{
	class Material : public Component
	{
	public:
		Material() {}
		Shader *shader;
	};
}