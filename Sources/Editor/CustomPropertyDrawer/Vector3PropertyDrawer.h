#pragma once

#include "glm/glm.hpp"
#include <rttr/registration>
using namespace rttr;

namespace BorderlessEditor
{
    class Vector3PropertyDrawer
    {
    public:
        static void Draw(const rttr::property &property, Component *componentPointer)
        {
            auto propertyValue = property.get_value(componentPointer);
            if (propertyValue.is_type<glm::vec3>())
            {
                auto &position = propertyValue.get_value<glm::vec3>();
                float f3[3] = {position.x, position.y, position.z};
                ImGui::InputFloat3(property.get_name().to_string().c_str(), f3);
                position.x = f3[0];
                position.y = f3[1];
                position.z = f3[2];
                property.set_value(componentPointer, position);
            }
        }
    };
}