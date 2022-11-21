#pragma once
#include "Component.h"
#include "Vector3.h"
#include "glm/glm.hpp"

namespace BorderlessEngine
{
	class Transform : public Component
	{
	public:
		Transform()
		{
			position = glm::vec3(0.0f, 0.0f, 0.0f);
			Front = glm::vec3(0.0f, 0.0f, 1.0f);
			Right = glm::vec3(1.0f, 0.0f, 0.0f);
			Up = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		// calculates the front vector from the Camera's (updated) Euler Angles
		void UpdateImmediately()
		{
		}

		glm::vec3 position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		// euler Angles
		float Yaw;
		float Pitch;

	private:
	};
}