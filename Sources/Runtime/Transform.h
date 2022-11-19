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
			WorldUp =  glm::vec3(0.0f, 1.0f, 0.0f);

			// calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			// also re-calculate the Right and Up vector
			Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			Up = glm::normalize(glm::cross(Right, Front));
		}
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