#pragma once
#include "MeshFileHead.h"
#include <vector>
#include "Vertex.h"

using namespace std;

namespace BorderlessEngine
{
    struct MyMesh
    {
    public:
        MyMesh(vector<Vertex> vertices, vector<unsigned int> indices)
        {
            
        }
        MeshFileHead head;
    };
}