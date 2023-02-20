#pragma once
#include <string>

class AssetImportContext
{
public:
    AssetImportContext(std::string path) : path(path) {}
    const std::string path;
};