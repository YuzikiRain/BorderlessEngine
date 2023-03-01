#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Render/Model/Mesh.h"
#include "Render/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Object.h"

using std::string;
using std::vector;

namespace BorderlessEngine
{
	class Model : public Object
	{
	public:
		Model(string const &path, bool gamma = false);
		void Draw(Shader &shader);
		vector<Mesh> ExportMesh();

	private:
		vector<Mesh> meshes;
		bool gammaCorrection;
		// model data
		vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		string directory;

		void loadModel(string const &path);
		/// <summary>
		/// 递归地处理每个节点，取得网格信息
		/// </summary>
		/// <param name="node"></param>
		/// <param name="scene"></param>
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName);
		unsigned int TextureFromFile(const char *path, const string &directoryPath, bool gamma = false);
	};
}