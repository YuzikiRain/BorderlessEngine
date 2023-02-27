#pragma once
#include "ScriptedImporter.h"
#include <fstream>
#include <vector>
#include "AssetDatabase.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "Render/Model/Vertex.h"
#include "Render/Model/Mesh.h"
#include "Render/Model/MeshFileHead.h"
#include "Render/Model/MyMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// #define STB_IMAGE_IMPLEMENTATION
#include "stb-image/stb_image.h"

using namespace std;
using namespace BorderlessEngine;

const char *modelFilter = "Model (*.obj)\0*.obj\0";
const char *modelFileExtension = "obj";
const char *meshFileExtension = "mesh";

Assimp::Importer importer;
const aiScene *scene;

namespace BorderlessEditor
{
    class ModelImporter : ScriptedImporter
    {
    public:
        // ModelImporter(std::string path) : ScriptedImporter(path) {}
        void OnImportAsset(AssetImportContext context)
        {
            auto path = context.path;
            auto newPath = context.newPath;
            auto modelPrefab = loadModel(path);
            auto p = &modelPrefab;
            AssetDatabase::SaveAsset(modelPrefab, newPath);
            return;

            // YAML::Node meshNode;
            // auto model = new BorderlessEngine::Model(path);
            // auto meshes = model->ExportMesh();
            // for (size_t i = 0; i < meshes.size(); i++)
            // {
            //     auto mesh = meshes[i];
            //     for (size_t j = 0; j < mesh.vertices.size(); j++)
            //     {
            //         auto vertex = meshNode["meshes"][i]["vertices"][j];
            //         auto position = vertex["position"];
            //         position["x"] = mesh.vertices[i].Position.x;
            //         position["y"] = mesh.vertices[i].Position.y;
            //         position["z"] = mesh.vertices[i].Position.z;
            //     }
            // }

            MeshFileHead mesh_file_head;
            mesh_file_head.type_[0] = 'm';
            mesh_file_head.type_[1] = 'e';
            mesh_file_head.type_[2] = 's';
            mesh_file_head.type_[3] = 'h';

            // int i = 0;
            // for (auto mesh : meshes)
            // {
            //     mesh_file_head.vertex_num_ = mesh.vertices.size();
            //     mesh_file_head.vertex_index_num_ = mesh.indices.size();

            //     std::fstream output_file_stream;
            //     // 原地生成对应的专用mesh资产
            //     auto newPath = path.substr(0, path.find(string(".") + modelFileExtension));
            //     newPath = newPath + to_string(i) + string(".") + meshFileExtension;
            //     output_file_stream.open(newPath, ios::out | ios::binary);

            //     // 写入文件头
            //     output_file_stream.write((char *)&mesh_file_head, sizeof(mesh_file_head));
            //     // 写入顶点数据
            //     output_file_stream.write((char *)&mesh.vertices[0], mesh_file_head.vertex_num_ * sizeof(Vertex));
            //     // 写入索引数据
            //     output_file_stream.write((char *)&mesh.indices[0], mesh_file_head.vertex_index_num_ * sizeof(unsigned int));

            //     output_file_stream.close();
            // }
        }

    private:
        string directory;
        vector<BorderlessEngine::MyMesh> meshes;
        vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

        GameObject *loadModel(string const &path)
        {
            // read file via ASSIMP
            // Assimp::Importer importer;
            // const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            // check for errors
            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
                return NULL;
            }
            // retrieve the directory path of the filepath
            directory = path.substr(0, path.find_last_of('/'));
            auto name = path.substr(path.find_last_of('/') + 1);

            auto modelPrefab = new GameObject(name.c_str());
            auto t = modelPrefab->AddComponent<Transform>();
            // process ASSIMP's root node recursively
            processNode(scene->mRootNode, scene, t);
            return NULL;
            

            return modelPrefab;
        }

        /// <summary>
        /// 递归地处理每个节点，取得网格信息
        /// </summary>
        /// <param name="node"></param>
        /// <param name="scene"></param>
        void processNode(aiNode *node, const aiScene *scene, Transform& transform)
        {
            // process each mesh located at the current node
            for (unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                // the node object only contains indices to index the actual objects in the scene.
                // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(mesh, scene));
                processMesh(mesh, scene);

                auto name = mesh->mName.C_Str();
                auto child = new GameObject(name != "" ? name : "mesh" + i);
                auto childTransform = child->AddComponent<Transform>();
                childTransform.Parent = &transform;
                transform.Children.push_back(&childTransform);
                // child->AddComponent<MeshFilter>();
            }
            // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
            for (unsigned int i = 0; i < node->mNumChildren; i++)
            {
                auto name = node->mName.C_Str();
                auto child = new GameObject(name != "" ? name : "gameObject" + i);
                auto childTransform = child->AddComponent<Transform>();
                childTransform.Parent = &transform;
                transform.Children.push_back(&childTransform);

                processNode(node->mChildren[i], scene, childTransform);
            }
        }

        BorderlessEngine::MyMesh processMesh(aiMesh *mesh, const aiScene *scene)
        {
            // data to fill
            vector<Vertex> vertices;
            vector<unsigned int> indices;
            vector<Texture> textures;

            // walk through each of the mesh's vertices
            for (size_t i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
                // normals
                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    vertex.Normal = vector;
                }
                // texture coordinates
                if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    glm::vec2 vec;
                    // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                    // tangent
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.Tangent = vector;
                    // bitangent
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.Bitangent = vector;
                }
                else
                    vertex.TexCoords = glm::vec2(0.0f, 0.0f);

                vertices.push_back(vertex);
            }
            // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                // retrieve all indices of the face and store them in the indices vector
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
            if (mesh->mMaterialIndex >= 0)
            {
                // process materials
                aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
                // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
                // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
                // Same applies to other texture as the following list summarizes:
                // diffuse: texture_diffuseN
                // specular: texture_specularN
                // normal: texture_normalN

                // 1. diffuse maps
                vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                // 2. specular maps
                vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
                // 3. normal maps
                std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
                textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
                // 4. height maps
                std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
                textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            }

            // return a mesh object created from the extracted mesh data
            // return BorderlessEngine::MyMesh(vertices, indices, textures);
            return BorderlessEngine::MyMesh(vertices, indices);
        }

        vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName)
        {
            vector<Texture> textures;
            for (size_t i = 0; i < material->GetTextureCount(type); i++)
            {
                aiString str;
                material->GetTexture(type, i, &str);
                // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
                bool skip = false;
                for (unsigned int j = 0; j < textures_loaded.size(); j++)
                {
                    if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                    {
                        textures.push_back(textures_loaded[j]);
                        skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                        break;
                    }
                }
                if (!skip)
                { // if texture hasn't been loaded already, load it
                    Texture texture;
                    // // 不知道为什么，这里的str.data字符数组的前4个字符都是0，所以只能从4开始读取
                    char *realPath = &str.data[4];
                    texture.id = TextureFromFile(realPath, directory);
                    // texture.id = TextureFromFile(str.C_Str(), directory);
                    texture.type = typeName;
                    texture.path = realPath;
                    // texture.path = str.C_Str();
                    textures.push_back(texture);
                    textures_loaded.push_back(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
                }
            }
            return textures;
        }

        unsigned int TextureFromFile(const char *path, const string &directoryPath, bool gamma = false)
        {
            string filename = string(path);
            filename = directory + '/' + filename;

            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }

            return textureID;
        }
    };
}