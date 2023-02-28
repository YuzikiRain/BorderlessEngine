#pragma once
#include <string>

using namespace std;

namespace BorderlessEditor
{
    class EditorProjectManager
    {
    public:
        static string OpenProject(string projectPath)
        {
            // 判断工程目录是否合法

            
            hasInitialized = true;
            return projectPath;
        }

        static void CloseProject()
        {
            hasInitialized = false;
        }

        static bool HasOpened()
        {
            return hasInitialized;
        }

    private:
        static inline bool hasInitialized;
    };
}