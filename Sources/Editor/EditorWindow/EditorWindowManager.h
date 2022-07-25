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
        static std::vector<EditorWindow *> *GetAllEditorwindows();
        static void Init();

    private:
        static Inspector *inspector;
        static Hierarchy *hierarchy;
        static std::vector<EditorWindow *> *editorWindows;
    };
}