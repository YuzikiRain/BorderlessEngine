#include "EditorWindow/EditorWindowManager.h"
#include "EditorWindow/EditorWindow.h"
#include "EditorWindow/Inspector.h"
#include "EditorWindow/Hierarchy.h"
#include <vector>

// #include <stdio.h>
// #include <Windows.h>
// #include <tchar.h>

namespace BorderlessEditor
{
    Inspector *EditorWindowManager::inspector = 0;
    Hierarchy *EditorWindowManager::hierarchy = 0;
    std::vector<EditorWindow *> *EditorWindowManager::editorWindows = new std::vector<EditorWindow *>();

    void EditorWindowManager::Init()
    {
        EditorWindowManager::inspector = new Inspector();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::inspector);
        EditorWindowManager::hierarchy = new Hierarchy();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::hierarchy);
    }

    std::vector<EditorWindow *> *EditorWindowManager::GetAllEditorwindows()
    {
        return editorWindows;
    }
}