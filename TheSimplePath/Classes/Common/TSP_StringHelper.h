/****************************************************************************
 * ==> TSP_StringHelper ----------------------------------------------------*
 ****************************************************************************
 * Description:  Helper class for strings                                   *
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
#include <string>
#include <mutex>

#define M_EOL   "\r\n"
#define M_WEOL L"\r\n"

/**
* Helper class for strings
*@author Jean-Milost Reymond
*/
class TSP_StringHelper
{
    public:
        /**
        * A thread-safe version of the std::setLocale() function
        *@param category - locale category identifier, one of the LC_xxx macros, may be 0
        *@param pLocale - new locale to select, system locale if nullptr
        *@return previously selected locale
        */
        static std::string SetLocale_ThreadSafe(std::int32_t category, const char* pLocale);

        /**
        * Replaces the chars in the string matching with the pattern by a substitution char
        *@param str - string in which chars should be replaced
        *@param pattern - chars pattern to replace
        *@param by - char to replace by
        *@return string with replaced chars
        */
        template <class T>
        static std::basic_string<T> ReplaceChars(const std::basic_string<T>& str, const std::basic_string<T>& pattern, T by);

        /**
        * Searches for a string occurrence in another string, and replaces by a replacement string
        *@param str - string to scan
        *@param search - string to search
        *@param replace - string to replace by
        *@param all - if true, all string occurrence will be replaced, only first occurrence if false
        *@return processed string
        */
        template<class T>
        static std::basic_string<T> SearchAndReplace(const std::basic_string<T>& str,
                                                     const std::basic_string<T>& search,
                                                     const std::basic_string<T>& replace,
                                                     bool                        all);

        /**
        * Fills a line with a character
        *@param text - text which will be surrounded with the char
        *@param fillChar - fill char
        *@param lineLength - line length
        *@return filled line
        */
        template<class T>
        static std::basic_string<T> Fill(const std::basic_string<T>& text, T fillChar, std::size_t lineLength);

        /**
        * Trims text (i.e. remove spaces before and after text)
        *@param value - value to trim
        *@return trimmed value
        */
        template<class T>
        static std::basic_string<T> Trim(const std::basic_string<T>& value);

        /**
        * Checks if a character is an ASCII letter (i.e a letter between a to z or A to Z)
        *@param c - character to check
        *@return true if character is an ASCII letter, otherwise false
        */
        static inline bool IsASCIILetter(char    c);
        static inline bool IsASCIILetter(wchar_t c);

        /**
        * Checks if a character contains a number
        *@param c - character to check
        *@param strict - if true, only characters from '0' to '9' will be accepted, see note below
        *@return true if character contains a number, otherwise false
        *@note If strict mode is disabled, other non-numeric characters which may be a part of a number,
        *      as e.g. '.' or '-' will also be accepted as valid numeric chars. This may be useful when
        *      IsNumeric() is used e.g. to determine if a string can be converted to number
        */
        static inline bool IsNumeric(char    c, bool strict);
        static inline bool IsNumeric(wchar_t c, bool strict);

        /**
        * Checks if a character is a space (including Japanese spaces) or a tab
        *@param c - character to check
        *@return true if the character is a space, otherwise false
        */
        static inline bool IsSpace(const char    c);
        static inline bool IsSpace(const wchar_t c);

        /**
        * Converts string to lower case
        *@param str - string to convert
        *@return converted string
        */
        static std::string  ToLowerCase(const std::string&  str);
        static std::wstring ToLowerCase(const std::wstring& str);

        /**
        * Converts string to upper case
        *@param str - string to convert
        *@return converted string
        */
        static std::string  ToUpperCase(const std::string&  str);
        static std::wstring ToUpperCase(const std::wstring& str);

        /**
        * Converts an Utf8 encoded string to Utf16
        *@param str - string to convert
        *@return converted string
        */
        static std::wstring Utf8ToUtf16(const std::string& str);

        /**
        * Converts an Utf16 encoded string to Utf8
        *@param str - string to convert
        *@return converted string
        */
        static std::string Utf16ToUtf8(const std::wstring& str);

        /**
        * Converts a boolean value to string
        *@param value - boolean value to convert
        *@param numeric - if true, the converted string will contain 0/1 instead of true/false
        *@return converted string
        */
        static std::string BoolToStr(bool value, bool numeric = false);

        /**
        * Converts a boolean value to Unicode string
        *@param value - boolean value to convert
        *@param numeric - if true, the converted string will contain 0/1 instead of true/false
        *@return converted string
        */
        static std::wstring BoolToWStr(bool value, bool numeric = false);

        /**
        * Converts a string to a boolean value
        *@param str - string to convert
        *@return converted boolean value
        */
        static bool StrToBool(const std::string&  str);
        static bool StrToBool(const std::wstring& str);
};

//---------------------------------------------------------------------------
// TSP_StringHelper
//---------------------------------------------------------------------------
template <class T>
std::basic_string<T> TSP_StringHelper::ReplaceChars(const std::basic_string<T>& str, const std::basic_string<T>& pattern, T by)
{
    std::basic_string<T> result;

    // iterate through chars in file name
    for each (auto c in str)
    {
        // check if char match an item in the pattern, write the replacing char if do filter,
        // otherwise copy char from source file name
        if (pattern.find(c) != std::basic_string<T>::npos)
            result += by;
        else
            result += c;
    }

    return result;
}
//---------------------------------------------------------------------------
template<class T>
std::basic_string<T> TSP_StringHelper::SearchAndReplace(const std::basic_string<T>& str,
                                                        const std::basic_string<T>& search,
                                                        const std::basic_string<T>& replace,
                                                        bool                        all)
{
    // is source string empty?
    if (str.empty())
        return std::basic_string<T>();

    // is text to search empty?
    if (search.empty())
        return std::basic_string<T>();

    std::basic_string<T> result = str;

    // begin search on first character
    std::size_t position = 0;

    // found search occurrence
    while ((position = result.find(search, position)) != result.npos)
    {
        // replace occurrence
        result.replace(position, search.length(), replace);

        // do replace all occurrences?
        if (!all)
            return result;

        // calculate next search position
        position += replace.length();
    }

    return result;
}
//---------------------------------------------------------------------------
template<class T>
std::basic_string<T> TSP_StringHelper::Fill(const std::basic_string<T>& text, T fillChar, std::size_t lineLength)
{
    if (text.length() >= lineLength)
        return text;

          std::basic_string<T> rawLine(lineLength, fillChar);
    const std::size_t          startPos = ((lineLength - text.length()) / 2);

    rawLine.replace(startPos, text.length(), text);
    return rawLine;
}
//---------------------------------------------------------------------------
template<class T>
std::basic_string<T> TSP_StringHelper::Trim(const std::basic_string<T>& value)
{
    // value is empty?
    if (!value.length())
        return value;

    std::size_t startPos = 0;

    // search for first non space char
    for (std::size_t i = 0; i < value.length(); ++i)
        if (IsSpace(value[i]) && value[i] != T('\r') && value[i] != T('\n'))
        {
            startPos = i;
            break;
        }

    std::size_t endPos = value.length();

    // search for last non space char
    for (int i = value.length() - 1; i >= 0; --i)
        if (IsSpace(value[i]) && value[i] != T('\r') && value[i] != T('\n'))
        {
            endPos = i + 1;
            break;
        }

    // is start and end position identical or invalid?
    if (startPos >= endPos - 1)
        return std::basic_string<T>();

    // return trimmed string
    return value.substr(startPos, endPos - startPos);
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsASCIILetter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsASCIILetter(wchar_t c)
{
    return ((c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z'));
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsNumeric(char c, bool strict)
{
    return ((c >= '0' && c <= '9') || (!strict && (c == '-' || c == '.')));
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsNumeric(wchar_t c, bool strict)
{
    return ((c >= L'0' && c <= L'9') || (!strict && (c == L'-' || c == L'.')));
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsSpace(const char c)
{
    return c == ' ' || c == '\t';
}
//---------------------------------------------------------------------------
bool TSP_StringHelper::IsSpace(const wchar_t c)
{
    // '\x3000' is a Japanese space in UTF16
    return c == L' ' || c == L'\t' || c == L'\x3000';
}
//---------------------------------------------------------------------------
