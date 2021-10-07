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

//---------------------------------------------------------------------------
// TSP_FileHelper
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
