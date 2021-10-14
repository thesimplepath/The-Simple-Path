/****************************************************************************
 * ==> TSP_FileHelper ------------------------------------------------------*
 ****************************************************************************
 * Description:  Helper class for files and directories                     *
 * Contained in: Common                                                     *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - The Simple Path                                            *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#include "TSP_FileHelper.h"

// common classes
#include "TSP_StringHelper.h"
#include "TSP_Exception.h"

// libraries
#include <sys/stat.h>
#include "dirent.h"

// windows
#ifdef _WIN32
    #ifndef UNICODE
        #define UNICODE
    #endif

    #include <windows.h>
    #include <Shlobj.h>
#endif

//---------------------------------------------------------------------------
// TSP_FileHelper
//---------------------------------------------------------------------------
std::string TSP_FileHelper::GetDesktopDir()
{
    #if defined (_WIN32)
        CHAR desktop[MAX_PATH];
        std::memset(&desktop, 0, MAX_PATH);

        // get Windows desktop path
        if (SUCCEEDED(::SHGetFolderPathA(nullptr,
                                         CSIDL_DESKTOP,
                                         nullptr,
                                         SHGFP_TYPE_CURRENT,
                                         desktop)))
            return desktop;

        return "";
    #else
        #error "TSP_FileHelper::GetDesktopDir function is not implemented for this platform"
    #endif
}
//---------------------------------------------------------------------------
std::wstring TSP_FileHelper::GetDesktopDirW()
{
    #if defined (_WIN32)
        TCHAR desktop[MAX_PATH];
        std::memset(&desktop, 0, MAX_PATH);

        // get Windows desktop path
        if (SUCCEEDED(::SHGetFolderPathW(nullptr,
                                         CSIDL_DESKTOP,
                                         nullptr,
                                         SHGFP_TYPE_CURRENT,
                                         desktop)))
            return desktop;

        return L"";
    #else
        #error "TSP_FileHelper::GetDesktopDirW function is not implemented for this platform"
    #endif
}
//---------------------------------------------------------------------------
std::string TSP_FileHelper::GetAppName()
{
    #if defined (_WIN32)
        char result[MAX_PATH] = {0};

        return std::string(result, ::GetModuleFileNameA(nullptr, result, MAX_PATH));
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif
}
//---------------------------------------------------------------------------
std::wstring TSP_FileHelper::GetAppNameW()
{
    #if defined (_WIN32)
        wchar_t result[MAX_PATH] = {0};

        return std::wstring(result, ::GetModuleFileNameW(nullptr, result, MAX_PATH));
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif
}
//---------------------------------------------------------------------------
TSP_Version TSP_FileHelper::GetAppVersion()
{
    #if defined (_WIN32)
        // get application file name and dir
        const std::wstring fileName = GetAppNameW();

        TSP_Version version;
        BYTE*       pVersionInfo = nullptr;

        try
        {
            // get version info size and create version info container
            DWORD hHandle = 0;
            DWORD size    = ::GetFileVersionInfoSize(fileName.c_str(), &hHandle);
            pVersionInfo  = new BYTE[size];

            // get version info
            if (!::GetFileVersionInfo(fileName.c_str(), 0, size, pVersionInfo))
                // return empty version if failed
                return TSP_Version();

            UINT              len   = 0;
            VS_FIXEDFILEINFO* pVsfi = nullptr;

            // get file version
            ::VerQueryValue(pVersionInfo, L"\\", (void**)&pVsfi, &len);

            // convert file version to TSP_Version and returns result
            version.SetMajor  (HIWORD(pVsfi->dwFileVersionMS));
            version.SetMinor  (LOWORD(pVsfi->dwFileVersionMS));
            version.SetRelease(HIWORD(pVsfi->dwFileVersionLS));
            version.SetBuild  (LOWORD(pVsfi->dwFileVersionLS));
        }
        catch (...)
        {}

        // delete version info, if needed
        if (pVersionInfo)
            delete[] pVersionInfo;

        return version;
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif
}
//---------------------------------------------------------------------------
std::string TSP_FileHelper::EscapeForbiddenChars(const std::string& fileName, char by)
{
    #if defined (_WIN32)
        const std::string pattern = "<>:\"/\\|?*";
    #elif defined (__APPLE__)
        const std::string pattern = ":/";
    #elif defined (__linux__)
        const std::string pattern = "/";
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif

    return TSP_StringHelper::ReplaceChars(fileName, pattern, by);
}
//---------------------------------------------------------------------------
std::wstring TSP_FileHelper::EscapeForbiddenChars(const std::wstring& fileName, wchar_t by)
{
    #if defined (_WIN32)
        const std::wstring pattern = L"<>:\"/\\|?*";
    #elif defined (__APPLE__)
        const std::wstring pattern = L":/";
    #elif defined (__linux__)
        const std::wstring pattern = L"/";
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif

    return TSP_StringHelper::ReplaceChars(fileName, pattern, by);
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::FileExists(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::FileExists(const std::wstring& name)
{
    struct _stat buffer;
    return (_wstat(name.c_str(), &buffer) == 0);
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::DirExists(const std::string& name)
{
    struct stat statbuf;

    if (stat(RemoveDelimiter(name).c_str(), &statbuf) != 0)
        return false;

    return S_ISDIR(statbuf.st_mode);
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::DirExists(const std::wstring& name)
{
    struct _stat statbuf;

    if (_wstat(RemoveDelimiter(name).c_str(), &statbuf) != 0)
        return false;

    return S_ISDIR(statbuf.st_mode);
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::CreateDir(const std::string& name)
{
    #if defined (_WIN32)
        if (DirExists(name))
            return true;

        return ::CreateDirectoryA(name.c_str(), nullptr);
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::CreateDir(const std::wstring& name)
{
    #if defined (_WIN32)
        if (DirExists(name))
            return true;

        return ::CreateDirectoryW(name.c_str(), nullptr);
    #else
        M_THROW_EXCEPTION("Unknown operating system");
    #endif
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::GetDirContent(const std::string& dir, IFileNames& content, bool fullNames)
{
    // open directory
    DIR* pDir = ::opendir(dir.c_str());

    // succeeded?
    if (!pDir)
        return false;

    dirent* pEnt;

    // get directory content
    while ((pEnt = ::readdir(pDir)) != nullptr)
        if (fullNames)
        {
            // skip special items
            if (std::strcmp(pEnt->d_name, ".") == 0 || std::strcmp(pEnt->d_name, "..") == 0)
                continue;

            content.push_back(AppendDelimiter(dir) + pEnt->d_name);
        }
        else
            content.push_back(pEnt->d_name);

    closedir(pDir);

    return true;
}
//---------------------------------------------------------------------------
bool TSP_FileHelper::GetDirContent(const std::wstring& dir, IFileNamesW& content, bool fullNames)
{
    // open directory
    _WDIR* pDir = ::_wopendir(dir.c_str());

    // succeeded?
    if (!pDir)
        return false;

    _wdirent* pEnt;

    // get directory content
    while ((pEnt = ::_wreaddir(pDir)) != nullptr)
        if (fullNames)
        {
            // skip special items
            if (std::wcscmp(pEnt->d_name, L".") == 0 || std::wcscmp(pEnt->d_name, L"..") == 0)
                continue;

            content.push_back((AppendDelimiter(dir) + pEnt->d_name).c_str());
        }
        else
            content.push_back(pEnt->d_name);

    _wclosedir(pDir);

    return true;
}
//---------------------------------------------------------------------------
