#pragma once
#include "MeshFileHead.h"
#include <vector>
#include "Vertex.h"

using std::vector;

namespace BorderlessEngine
{
    struct MyMesh
    {
    public:
        MyMesh(vector<Vertex> vertices, vector<unsigned int> indices)
        {
        }
        MyMesh()
        {
        }
        MeshFileHead head;
    };
}