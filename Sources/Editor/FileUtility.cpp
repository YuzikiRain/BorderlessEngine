#include "FileUtility.h"
#include <string>
#include <shobjidl.h>
#include "Core/GLFWManager.h"
// 打开文件对话框
#include <commdlg.h>

// 打开目录对话框
#include <iostream>
#include <locale>
#include <codecvt>
#ifdef WIN32
#include <shlobj.h>
#endif

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

    /// @brief // 选择目录
    /// @param filter
    /// @param extension
    /// @return
    std::string FileUtility::OpenDirectoryDialogue()
    {
        BROWSEINFO bi;
        bi.hwndOwner = NULL;
        bi.pidlRoot = CSIDL_DESKTOP; // 文件夹的根目录，此处为桌面
        bi.pszDisplayName = NULL;
        bi.lpszTitle = NULL;                                                            // 显示位于对话框左上部的提示信息
        bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE; // 有新建文件夹按钮
        bi.lpfn = NULL;
        bi.iImage = 0;
        LPITEMIDLIST pidl = SHBrowseForFolder(&bi); // 调用选择对话框
        if (pidl == NULL)
        {
            std::cout << "没有选择目录" << std::endl;
            return NULL;
        }

        TCHAR strFolder[MAX_PATH];
        SHGetPathFromIDList(pidl, strFolder);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string sFolder(strFolder);

        return sFolder;
    }

}