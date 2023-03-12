#pragma once

#include "Component.h"
#include "Render/Shader.h"

namespace BorderlessEngine {
    class Material : public Component {
    public:
        Material() {}

        Shader *shader;

        YAML::Node Serialize() override {
            YAML::Node node;
            node["shader"] = shader->ID;
            return node;
        }
    };
}