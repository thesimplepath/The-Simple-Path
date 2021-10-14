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

#pragma once

// std
#include <ctime>
#include <vector>
#include <string>

// common classes
#include "TSP_Version.h"

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#if defined (_WIN32)
    #define M_DirDelim   '\\'
    #define M_DirDelimW L'\\'
#elif defined (__APPLE__)
    #define M_DirDelim   '/'
    #define M_DirDelimW L'/'
#endif

/**
* Helper class for files and directories
*@author Jean-Milost Reymond
*/
class TSP_FileHelper
{
    public:
        typedef std::vector<std::string>  IFileNames;
        typedef std::vector<std::wstring> IFileNamesW;

        /**
        * Gets Windows desktop directory
        *@return desktop directory, empty string on error
        */
        static std::string  GetDesktopDir();
        static std::wstring GetDesktopDirW();

        /**
        * Gets running application name and dir
        *@return running application name and dir
        */
        static std::string  GetAppName();
        static std::wstring GetAppNameW();

        /**
        * Gets running application version
        *@return running application version, empty version on error
        */
        static TSP_Version GetAppVersion();

        /**
        * Gets file directory from a full path
        *@param fullPath - full path containing file dir and name
        *@param keepLastChar - if true, last delimiter will be kept
        *@param delimiter - dir delimiter
        *@return directory, empty string on error
        */
        template <class T>
        static std::basic_string<T> GetFileDir(const std::basic_string<T>& fullPath, bool keepLastChar, T delimiter = T(M_DirDelim));

        /**
        * Gets file name from a full path
        *@param fullPath - full path containing file dir and name
        *@param delimiter - dir delimiter
        *@return file name
        */
        template <class T>
        static std::basic_string<T> GetFileName(const std::basic_string<T>& fullPath, T delimiter = T(M_DirDelim));

        /**
        * Gets file name from a full path, without extension
        *@param fullPath - full path containing file dir and name
        *@param delimiter - dir delimiter
        *@return file name
        */
        template <class T>
        static std::basic_string<T> GetStrippedFileName(const std::basic_string<T>& fullPath, T delimiter = T(M_DirDelim));

        /**
        * Gets file extension from a full path
        *@param fullPath - full path containing file dir and name
        *@return file extension
        */
        template <class T>
        static std::basic_string<T> GetFileExtension(const std::basic_string<T>& fullPath);

        /**
        * Appends delimiter at dir end
        *@param dirName - directory name to append to
        *@param delimiter - delimiter used in current system
        *@return appended dir name
        *@note If delimiter already exists at end, it will not be appended again
        */
        template <class T>
        static std::basic_string<T> AppendDelimiter(const std::basic_string<T>& dirName, T delimiter = T(M_DirDelim));

        /**
        * Remove delimiter from dir end
        *@param dirName - directory name to remove from
        *@param delimiter - delimiter used in current system
        *@return dir name without last delimiter
        *@note If delimiter not exists at end, nothing will be removed
        */
        template <class T>
        static std::basic_string<T> RemoveDelimiter(const std::basic_string<T>& dirName, T delimiter = T(M_DirDelim));

        /**
        * Escapes the forbidden chars in the file name and replaces by another char
        *@param fileName - file name in which forbidden chars should be replaced
        *@param pattern - forbidden chars pattern
        *@param by - char to replace by
        *@return escaped file name
        */
        static std::string  EscapeForbiddenChars(const std::string&  fileName, char    by =  '_');
        static std::wstring EscapeForbiddenChars(const std::wstring& fileName, wchar_t by = L'_');

        /**
        * Checks if a file exists
        *@param fileName - file name to check
        *@returns true if file exists, otherwise false
        */
        static bool FileExists(const std::string&  name);
        static bool FileExists(const std::wstring& name);

        /**
        * Checks if a directory exists
        *@param dirName - dir name to check
        *@returns true if dir exists, otherwise false
        */
        static bool DirExists(const std::string&  name);
        static bool DirExists(const std::wstring& name);

        /**
        * Creates a new directory
        *@param name - dir name to create
        *@return true on success, otherwise false
        *@note BE CAREFUL, this function does not verify if the new dir name is valid before using it
        */
        static bool CreateDir(const std::string&  name);
        static bool CreateDir(const std::wstring& name);

        /**
        * Checks if a path is a dir
        *@param name - dir name to check
        *@return true if name is a dir, otherwise false
        */
        template <class T>
        static bool IsDir(const std::basic_string<T>& name);

        /**
        * Gets directory content
        *@param dir - dir name for which content should be get
        *@param[out] content - dir content
        *@param fullNames - if true, items will contain full names
        *@return true on success, otherwise false
        *@note if fullNames is set, special "." and ".." items will be skipped
        */
        static bool GetDirContent(const std::string&  dir, IFileNames&  content, bool fullNames);
        static bool GetDirContent(const std::wstring& dir, IFileNamesW& content, bool fullNames);
};

//---------------------------------------------------------------------------
// TSP_FileHelper
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::GetFileDir(const std::basic_string<T>& fullPath, bool keepLastChar, T delimiter)
{
    // is source empty?
    if (fullPath.empty())
        return std::basic_string<T>();

    std::size_t position = 0;

    // iterate through full name chars
    for (int i = fullPath.length() - 1; i >= 0; --i)
        // found dir delimiter?
        if (fullPath[i] == delimiter)
        {
            // keep position
            position = i;
            break;
        }

    // is position valid?
    if (!position || (position + 1) >= fullPath.length())
        return std::basic_string<T>();

    // extract file dir
    std::basic_string<T> fileDir = fullPath.substr(0, (keepLastChar ? position + 1 : position));

    // do keep last char?
    if (keepLastChar)
        // check if last char exists, append if not
        return AppendDelimiter(fileDir, delimiter);

    return fileDir;
}
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::GetFileName(const std::basic_string<T>& fullPath, T delimiter)
{
    // is source empty?
    if (fullPath.empty())
        return std::basic_string<T>();

    std::size_t position = 0;

    // iterate through full name chars
    for (int i = fullPath.length() - 1; i >= 0; --i)
        // found dir delimiter?
        if (fullPath[i] == delimiter)
        {
            // keep position
            position = i;
            break;
        }

    // is position valid?
    if (!position || (position + 1) >= fullPath.length())
        return fullPath;

    // extract file name
    return fullPath.substr(position + 1, fullPath.length() - (position + 1));
}
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::GetStrippedFileName(const std::basic_string<T>& fullPath, T delimiter)
{
    // is source empty?
    if (fullPath.empty())
        return std::basic_string<T>();

    // first get file name
    std::basic_string<T> fileName = GetFileName(fullPath, delimiter);

    std::size_t position = 0;

    // iterate through full name chars
    for (int i = fileName.length() - 1; i >= 0; --i)
        // found extension marker?
        if (fileName[i] == T('.'))
        {
            // keep position
            position = i;
            break;
        }

    // is position valid?
    if (!position)
        return std::basic_string<T>();
    else
    if ((position + 1) >= fileName.length())
        return fileName;

    // extract stripped file name
    return fileName.substr(0, position);
}
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::GetFileExtension(const std::basic_string<T>& fullPath)
{
    // is source empty?
    if (fullPath.empty())
        return std::basic_string<T>();

    std::size_t position = 0;

    // iterate through full name chars
    for (int i = fullPath.length() - 1; i >= 0; --i)
        // found extension delimiter?
        if (fullPath[i] == T('.'))
        {
            // keep position
            position = i;
            break;
        }

    // is position valid?
    if (!position || (position + 1) >= fullPath.length())
        return fullPath;

    // extract file dir
    return fullPath.substr(position + 1, fullPath.length() - (position + 1));
}
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::AppendDelimiter(const std::basic_string<T>& dirName, T delimiter)
{
    // is dir name empty?
    if (dirName.empty())
        return std::basic_string<T>(1, delimiter);

    // dir name already contains delimiter at end?
    if (dirName[dirName.length() - 1] == delimiter)
        return dirName;

    // append delimiter
    return dirName + delimiter;
}
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_FileHelper::RemoveDelimiter(const std::basic_string<T>& dirName, T delimiter)
{
    // is dir name empty?
    if (dirName.empty())
        return std::basic_string<T>();

    // dir name contains delimiter at end?
    if (dirName[dirName.length() - 1] == delimiter)
        // remove it
        return dirName.substr(0, dirName.length() - 1);

    // dir is already terminated without delimiter
    return dirName;
}
//---------------------------------------------------------------------------
template <class T>
bool TSP_FileHelper::IsDir(const std::basic_string<T>& name)
{
    return DirExists(name);
}
//---------------------------------------------------------------------------
