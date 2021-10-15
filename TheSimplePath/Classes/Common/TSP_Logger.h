/****************************************************************************
 * ==> TSP_Logger ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a logger                                          *
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
#include <iostream>
#include <cstddef>
#include <string>
#include <mutex>

// common classes
#include "TSP_StringHelper.h"
#include "TSP_Version.h"
#include "TSP_Exception.h"

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_GetTimeStamp            L"[" << TSP_Logger::Instance()->GetTimeStamp(true) << L"] "
#define M_Log(msg)                *TSP_Logger::Instance()                   << msg << M_WEOL
#define M_LogT(msg)               *TSP_Logger::Instance() << M_GetTimeStamp << msg << M_WEOL
#define M_LogWarn(msg)            M_Log (L"<warning>" << msg << L"</warning>")
#define M_LogWarnT(msg)           M_LogT(L"<warning>" << msg << L"</warning>")
#define M_LogError(msg)           M_Log (L"<error>"   << msg << L"</error>")
#define M_LogErrorT(msg)          M_LogT(L"<error>"   << msg << L"</error>")
#define M_LogException(type, msg) M_Log (M_FORMAT_EXCEPTION(type, msg))
//---------------------------------------------------------------------------

/**
* Provides a logger
*@author Jean-Milost Reymond
*/
class TSP_Logger
{
    public:
        /**
        * Logger header
        */
        struct IHeader
        {
            std::wstring m_Name;
            TSP_Version  m_Version;
            std::size_t  m_ScreenWidth  = 0;
            std::size_t  m_ScreenHeight = 0;
            std::size_t  m_ScreenDPI    = 0;
        };

        /**
        * Gets the logger instance, creates it if still not exists
        *@return the logger instance
        *@throw RPM exception if instance could not be created
        */
        static TSP_Logger* Instance();

        /**
        * Releases the logger instance
        */
        static void Release();

        /**
        * Input stream operator
        *@param value - value to add to the log
        *@returns reference to itself
        */
        TSP_Logger& operator << (bool                value);
        TSP_Logger& operator << (std::int8_t         value);
        TSP_Logger& operator << (std::uint8_t        value);
        TSP_Logger& operator << (std::int16_t        value);
        TSP_Logger& operator << (std::uint16_t       value);
        TSP_Logger& operator << (std::int32_t        value);
        TSP_Logger& operator << (std::uint32_t       value);
        TSP_Logger& operator << (std::int64_t        value);
        TSP_Logger& operator << (std::uint64_t       value);
        TSP_Logger& operator << (float               value);
        TSP_Logger& operator << (double              value);
        TSP_Logger& operator << (const char*         pValue);
        TSP_Logger& operator << (const wchar_t*      pValue);
        TSP_Logger& operator << (const std::string&  value);
        TSP_Logger& operator << (const std::wstring& value);
        TSP_Logger& operator << (const std::tm&      value);

        /**
        * Clears the logger content
        */
        void Clear();

        /**
        * Opens the logger
        *@param header - header containing application info to log
        */
        void Open(const IHeader& header);

        /**
        * Closes the log
        */
        void TSP_Logger::Close();

        /**
        * Gets the log
        *@return the log
        */
        std::wstring Get() const;

        /**
        * Gets a time stamp
        *@param timeOnly - if true, only the time will be returned
        *@return the time stamp
        */
        std::wstring GetTimeStamp(bool timeOnly) const;

        /**
        * Gets a file name for the log
        *@param appName - application name
        */
        std::wstring GetFileName(const std::wstring& appName) const;

    private:
        static TSP_Logger*  m_pLogger;
        static std::mutex   m_Mutex;
               std::wstring m_Log;

        TSP_Logger();

        /**
        * Copy constructor
        *@param other - other logger to copy from
        */
        TSP_Logger(const TSP_Logger& other);

        ~TSP_Logger();

        /**
        * Copy operator
        *@param other - other logger to copy from
        */
        const TSP_Logger& operator = (const TSP_Logger& other);
};
