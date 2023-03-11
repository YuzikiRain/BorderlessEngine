#pragma once
#include "Entity.h"
#include <string>

#include "ISerializable.h"

namespace BorderlessEngine
{
	class Object : public Entity, public ISerializable
	{
	public:
		std::string Name;
		std::string Path;

		~Object(){};

		YAML::Node Serialize()
		{
			YAML::Node node;
			node["Name"] = Name;
			node["Path"] = Path;

			return node;
		}
	private:
	};
}