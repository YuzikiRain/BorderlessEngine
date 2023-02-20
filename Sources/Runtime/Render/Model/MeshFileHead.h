#pragma once

struct MeshFileHead
{
    char type_[4];
    int vertex_num_;       // 顶点个数
    int vertex_index_num_; // 索引个数
};