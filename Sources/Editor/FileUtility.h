#pragma once

#include <string>

namespace BorderlessEditor
{
    class FileUtility
    {
    public:
        static std::string OpenFileDialogue(const char *filter, const char *extension);
        static std::string SaveFileDialogue(const char *filter, const char *extension);
    };
}