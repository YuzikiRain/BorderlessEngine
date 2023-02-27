#pragma once
#include <rttr/registration>
using namespace rttr;

#include "Component.h"
#include "Transform.h"
#include "glm/glm.hpp"
#include "MeshFilter.h"

RTTR_REGISTRATION
{
	registration::class_<BorderlessEngine::Component>("Component")
		.constructor<>();

	registration::class_<BorderlessEngine::MeshFilter>("MeshFilter")
		.constructor<>()
		.property("Mesh", &BorderlessEngine::MeshFilter::Mesh)
		.property("Model", &BorderlessEngine::MeshFilter::Model);

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