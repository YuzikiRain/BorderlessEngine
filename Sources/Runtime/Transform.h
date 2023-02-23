#pragma once
#include <vector>
#include "Component.h"
#include "Vector3.h"
#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <rttr/registration>
using namespace rttr;

namespace BorderlessEngine
{
	class Transform : public Component
	{
	public:
		Transform()
		{
			Position = glm::vec3(0.0f, 0.0f, 0.0f);

			Yaw = 0.0f;
			Pitch = 0.0f;
			Roll = 0.0f;

			UpdateImmediately();

			Children = vector<Transform *>();
		}
		// calculates the front vector from the Camera's (updated) Euler Angles
		void UpdateImmediately()
		{
			glm::vec3 eulerAnglesInDegrees(Pitch, Yaw, Roll);
			glm::vec3 eulerAnglesInRadians = glm::radians(eulerAnglesInDegrees);
			Quaternion = glm::quat(eulerAnglesInRadians);

			// opengl世界空间坐标系是右手坐标系，如果右方和上方分别对应屏幕的右方和上方，则屏幕前方应该指向(0,0,-1)
			Front = Quaternion * glm::vec3(0.0f, 0.0f, -1.0f);
			Right = Quaternion * glm::vec3(1.0f, 0.0f, 0.0f);
			Up = Quaternion * glm::vec3(0.0f, 1.0f, 0.0f);
		}

		glm::mat4 GetMatrix()
		{
			return glm::translate(glm::toMat4(Quaternion), Position);
		}

		glm::vec3 GetEuler()
		{
			return glm::degrees(glm::eulerAngles(Quaternion));
		}

		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::quat Quaternion;

		// euler Angles
		float Yaw;
		float Pitch;
		float Roll;

		int childIndex;
		vector<Transform *> Children;
		Transform *Parent;

	private:
		;

		RTTR_ENABLE(Component)
	};
}

RTTR_REGISTRATION
{
	registration::class_<BorderlessEngine::Component>("Component")
		.constructor<>();

	registration::class_<BorderlessEngine::Transform>("Transform")
		.constructor<>()
		// .property("Yaw", &BorderlessEngine::Transform::Yaw)
		.property("Position", &BorderlessEngine::Transform::Position)
		.method("GetMatrix", &BorderlessEngine::Transform::GetMatrix);

	registration::class_<glm::vec3>("glm::vec3")
		.constructor<>()
		.property("x", &glm::vec3::x)
		.property("y", &glm::vec3::y)
		.property("z", &glm::vec3::z)
		.method("length", &glm::vec3::length);
}

// namespace YAML
// {
// 	template <>
// 	struct convert<glm::vec3>
// 	{
// 		static Node encode(const glm::vec3 &rhs)
// 		{
// 			Node node;
// 			node.push_back(rhs.x);
// 			node.push_back(rhs.y);
// 			node.push_back(rhs.z);
// 			return node;
// 		}

// 		static bool decode(const Node &node, glm::vec3 &rhs)
// 		{
// 			if (!node.IsSequence() || node.size() != 3)
// 			{
// 				return false;
// 			}

// 			rhs.x = node[0].as<float>();
// 			rhs.y = node[1].as<float>();
// 			rhs.z = node[2].as<float>();
// 			return true;
// 		}
// 	};
// }
