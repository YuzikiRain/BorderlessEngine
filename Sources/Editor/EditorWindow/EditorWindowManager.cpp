#include "EditorWindow/EditorWindowManager.h"
#include "EditorWindow/EditorWindow.h"
#include "EditorWindow/Inspector.h"
#include "EditorWindow/Hierarchy.h"
#include "EditorWindow/GameEditorWindow.h"
#include "EditorWindow/SceneEditorWindow.h"
#include "EditorWindow/AssetBrowser.h"
#include <vector>

namespace BorderlessEditor
{
    Inspector *EditorWindowManager::inspector = 0;
    Hierarchy *EditorWindowManager::hierarchy = 0;
    SceneEditorWindow *EditorWindowManager::scene = 0;
    GameEditorWindow *EditorWindowManager::game = 0;
    AssetBrowser *EditorWindowManager::assetBrowser = 0;
    std::vector<EditorWindow *> *EditorWindowManager::editorWindows = new std::vector<EditorWindow *>();

    void EditorWindowManager::Init()
    {
        EditorWindowManager::inspector = new Inspector();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::inspector);
        EditorWindowManager::hierarchy = new Hierarchy();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::hierarchy);
        EditorWindowManager::scene = new SceneEditorWindow();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::scene);
        EditorWindowManager::game = new GameEditorWindow();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::game);
        EditorWindowManager::assetBrowser = new AssetBrowser();
        EditorWindowManager::editorWindows->push_back(EditorWindowManager::assetBrowser);
    }

    std::vector<EditorWindow *> *EditorWindowManager::GetAllEditorwindows()
    {
        return editorWindows;
    }
}