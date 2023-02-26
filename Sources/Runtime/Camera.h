#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace BorderlessEngine
{
	class Camera : public Component
	{
	public:
		Camera() {}
		float fov = 60.0f;
		float nearPlane = 0.01f;
		float farPlane = 100.0f;
	};
}