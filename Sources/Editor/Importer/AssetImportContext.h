#pragma once
#include <string>

using namespace std;

class AssetImportContext
{
public:
    AssetImportContext(string path, string newPath) : path(path), newPath(newPath) {}
    const string path;
    const string newPath;
};