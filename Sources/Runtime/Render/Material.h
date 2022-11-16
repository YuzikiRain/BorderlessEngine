#pragma once
#include "Component.h"
#include "Shader.h"

namespace BorderlessEngine
{
	class Material : public Component
	{
	public:
		Material();
		Shader *shader;
	};
}