#include "EditorWindow/EditorWindowManager.h"
#include "EditorWindow/EditorWindow.h"
#include "EditorWindow/Inspector.h"
#include "EditorWindow/Hierarchy.h"
#include "EditorWindow/GameEditorWindow.h"
#include <vector>

namespace BorderlessEditor
{
    Inspector *EditorWindowManager::inspector = 0;
    Hierarchy *EditorWindowManager::hierarchy = 0;
    GameEditorWindow *EditorWindowManager::game = 0;
    std::vector<EditorWindow *> *EditorWindowManager::editorWindows = new std::vector<EditorWindow *>();

    void EditorWindowManager::Init()
    {
        EditorWindowManager::inspector = new Inspector();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::inspector);
        EditorWindowManager::hierarchy = new Hierarchy();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::hierarchy);
        EditorWindowManager::game = new GameEditorWindow();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::game);
    }

    std::vector<EditorWindow *> *EditorWindowManager::GetAllEditorwindows()
    {
        return editorWindows;
    }
}