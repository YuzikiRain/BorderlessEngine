#include "FileUtility.h"
#include <string>
#include <shobjidl.h>
#include "Core/GLFWUtility.h"
// 打开文件对话框
#include <commdlg.h>

namespace BorderlessEditor
{
    std::string FileUtility::OpenFileDialogue(const char *filter, const char *extension)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = BorderlessEngine::GLFWManager::GetWin32Window();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrDefExt = extension;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        else
            return std::string();
    }

    std::string FileUtility::SaveFileDialogue(const char *filter, const char *extension)
    {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = {0};
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = BorderlessEngine::GLFWManager::GetWin32Window();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.lpstrDefExt = extension;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;
        else
            return std::string();
    }
}