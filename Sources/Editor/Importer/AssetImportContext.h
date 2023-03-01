#pragma once
#include <string>

using std::string;

class AssetImportContext
{
public:
    AssetImportContext(string path, string newPath) : path(path), newPath(newPath) {}
    const string path;
    const string newPath;
};