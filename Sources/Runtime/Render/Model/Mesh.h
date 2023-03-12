#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Render/Shader.h"
#include "Object.h"
#include "Vertex.h"
#include "Texture.h"

using std::vector;

namespace BorderlessEngine
{
	class Mesh : public Object
	{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		Mesh();
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);

        YAML::Node Serialize() override {
            YAML::Node node;
            node["test"] = "ttt";
            return node;
        }

	private:
		unsigned int VAO, VBO, EBO;
		void setupMesh();
	};
}