#pragma once
#include "Component.h"
#include "Vector3.h"
#include "glm/glm.hpp"

namespace BorderlessEngine
{
	class Transform : public Component
	{
	public:
		Transform();
		// calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors();

		glm::vec3 position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// euler Angles
		float Yaw;
		float Pitch;

	private:
	};
}