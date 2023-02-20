#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Render/Shader.h"
#include "Object.h"

using namespace std;

namespace BorderlessEngine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	struct Texture
	{
		unsigned int id;
		string type;
		string path;
	};

	class Mesh : public Object
	{
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		Mesh();
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void Draw(Shader shader);

	private:
		unsigned int VAO, VBO, EBO;
		void setupMesh();
	};
}