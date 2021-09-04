/****************************************************************************
 * ==> RPM_Logger ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a logger                                          *
 * Contained in: Common                                                     *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - todo FIXME -cFeature -oJean: Set the project name here     *
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
#include "RPM_StringHelper.h"
#include "RPM_Version.h"

// macros
#define M_GetTimeStamp   L"[" << RPM_Logger::Instance()->GetTimeStamp(true) << L"] "
#define M_Log(msg)       *RPM_Logger::Instance()                                   << msg                  << M_WEOL
#define M_LogT(msg)      *RPM_Logger::Instance() << M_GetTimeStamp                 << msg                  << M_WEOL
#define M_LogWarn(msg)   *RPM_Logger::Instance()                   << L"<warning>" << msg << L"</warning>" << M_WEOL
#define M_LogWarnT(msg)  *RPM_Logger::Instance() << M_GetTimeStamp << L"<warning>" << msg << L"</warning>" << M_WEOL
#define M_LogError(msg)  *RPM_Logger::Instance()                   << L"<error>"   << msg << L"</error>"   << M_WEOL
#define M_LogErrorT(msg) *RPM_Logger::Instance() << M_GetTimeStamp << L"<error>"   << msg << L"</error>"   << M_WEOL

/**
* Provides a logger
*@author Jean-Milost Reymond
*/
class RPM_Logger
{
    public:
        /**
        * Logger header
        */
        struct IHeader
        {
            std::wstring m_Name;
            RPM_Version  m_Version;
            std::size_t  m_ScreenWidth  = 0;
            std::size_t  m_ScreenHeight = 0;
            std::size_t  m_ScreenDPI    = 0;
        };

        /**
        * Gets the generator instance, creates it if still not exists
        *@return the generator instance
        *@throw A runtime error if instance could not be created
        */
        static RPM_Logger* Instance();

        /**
        * Input stream operator
        *@param value - value to add to the log
        *@returns reference to itself
        */
        RPM_Logger& operator << (bool                value);
        RPM_Logger& operator << (std::int8_t         value);
        RPM_Logger& operator << (std::uint8_t        value);
        RPM_Logger& operator << (std::int16_t        value);
        RPM_Logger& operator << (std::uint16_t       value);
        RPM_Logger& operator << (std::int32_t        value);
        RPM_Logger& operator << (std::uint32_t       value);
        RPM_Logger& operator << (std::int64_t        value);
        RPM_Logger& operator << (std::uint64_t       value);
        RPM_Logger& operator << (float               value);
        RPM_Logger& operator << (double              value);
        RPM_Logger& operator << (const char*         pValue);
        RPM_Logger& operator << (const wchar_t*      pValue);
        RPM_Logger& operator << (const std::string&  value);
        RPM_Logger& operator << (const std::wstring& value);
        RPM_Logger& operator << (const std::tm&      value);

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
        void RPM_Logger::Close();

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

    private:
        static RPM_Logger*  m_pLogger;
        static std::mutex   m_Mutex;
               std::wstring m_Log;

        RPM_Logger();

        /**
        * Copy constructor
        *@param other - other identifier generator to copy from
        */
        RPM_Logger(const RPM_Logger& other);

        ~RPM_Logger();

        /**
        * Copy operator
        *@param other - other logger to copy from
        */
        const RPM_Logger& operator = (const RPM_Logger& other);
};
