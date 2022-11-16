#pragma once
#include "Component.h"
#include "Vector3.h"

namespace BorderlessEngine
{
	class Transform : public Component
	{
	public:
		Transform();
		Vector3 *position;

	private:
	};
}