#pragma once

#include "EditorWindow/EditorWindow.h"
#include "EditorWindow/Inspector.h"
#include "EditorWindow/Hierarchy.h"
#include <vector>

// #include <stdio.h>
// #include <Windows.h>
// #include <tchar.h>

namespace BorderlessEditor
{
    class EditorWindowManager
    {
    public:
        static void Init()
        {
            inspector = new Inspector();
            windows.push_back(inspector);
            hierarchy = new Hierarchy();
            windows.push_back(hierarchy);
        }

        static std::vector<EditorWindow *> GetAllEditorwindows() { return windows; }

    private:
        static Inspector *inspector;
        static Hierarchy *hierarchy;
        static std::vector<EditorWindow *> windows;
    };
}