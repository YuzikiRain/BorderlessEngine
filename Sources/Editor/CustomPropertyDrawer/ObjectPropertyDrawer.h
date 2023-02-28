#pragma once

#include "glm/glm.hpp"
#include <rttr/registration>
using namespace rttr;

namespace BorderlessEditor
{
    class ObjectPropertyDrawer
    {
    public:
        static void Draw(const rttr::property &property, shared_ptr<Component> componentPointer)
        {
            auto propertyValue = property.get_value(componentPointer);
                auto &object = propertyValue.get_value<Object>();
                
                ImGui::LabelText("reference", object.Path.c_str());
                if (ImGui::SmallButton("·"))
                {

                }
                property.set_value(componentPointer, object);
        }
    };
}