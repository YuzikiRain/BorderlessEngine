#pragma once
#include "Entity.h"
#include <string>

namespace BorderlessEngine
{
	class Object : public Entity
	{
	private:
		std::string path;
	};
}