#pragma once
#include "Entity.h"
#include <string>

namespace BorderlessEngine
{
	class Object : public Entity
	{
	public:
		std::string Name;
		std::string Path;

	private:
	};
}