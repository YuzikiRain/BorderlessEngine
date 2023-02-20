#pragma once
#include <string>
#include "AssetImportContext.h"

class ScriptedImporter
{
public:
    // ScriptedImporter(std::string path);
    virtual void OnImportAsset(AssetImportContext context) = 0;

private:
};
