#pragma once

#include "imgui.h"
#include "glm/glm.hpp"

namespace BorderlessEditor
{
    class DefaultPropertyDrawer
    {
    public:
        virtual static void Draw() = 0;
    };
}