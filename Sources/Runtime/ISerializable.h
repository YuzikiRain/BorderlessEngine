#pragma once
#include "yaml-cpp/yaml.h"

class ISerializable
{
public:
    virtual YAML::Node Serialize() = 0;
};