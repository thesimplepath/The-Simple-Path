/****************************************************************************
 * ==> RPM_Logger ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a logger, to a file and/or to the console         *
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

#include "RPM_Logger.h"

// std
#include <locale>
#include <sstream>

// common classes
#include "RPM_Exception.h"
#include "RPM_StringHelper.h"
#include "RPM_TimeHelper.h"
#include "RPM_FileHelper.h"

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
RPM_Logger* RPM_Logger::m_pLogger = nullptr;
std::mutex  RPM_Logger::m_Mutex;
//---------------------------------------------------------------------------
// RPM_Logger
//---------------------------------------------------------------------------
RPM_Logger::RPM_Logger()
{}
//---------------------------------------------------------------------------
RPM_Logger::RPM_Logger(const RPM_Logger& other)
{
    M_THROW_EXCEPTION("Cannot create a copy of a singleton class");
}
//---------------------------------------------------------------------------
RPM_Logger::~RPM_Logger()
{}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (bool value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::int8_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::uint8_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::int16_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::uint16_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::int32_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::uint32_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::int64_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (std::uint64_t value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (float value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (double value)
{
    m_Log += std::to_wstring(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (const char* pValue)
{
    if (pValue)
        m_Log += RPM_StringHelper::Utf8ToUtf16(std::string(pValue));

    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (const wchar_t* pValue)
{
    if (pValue)
        m_Log += std::wstring(pValue);

    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (const std::string& value)
{
    m_Log += RPM_StringHelper::Utf8ToUtf16(value);
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (const std::wstring& value)
{
    m_Log += value;
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger& RPM_Logger::operator << (const std::tm& value)
{
    m_Log += RPM_StringHelper::Utf8ToUtf16(RPM_TimeHelper::TmToStr(value, "%F %T", ""));
    return *this;
}
//---------------------------------------------------------------------------
const RPM_Logger& RPM_Logger::operator = (const RPM_Logger& other)
{
    M_THROW_EXCEPTION("Cannot create a copy of a singleton class");

    // useless and never reached, but otherwise VS generates an error
    return *this;
}
//---------------------------------------------------------------------------
RPM_Logger* RPM_Logger::Instance()
{
    // check instance out of the thread lock (double check lock)
    if (!m_pLogger)
    {
        // lock up the thread
        std::unique_lock<std::mutex> lock(m_Mutex);

        // create the instance
        if (!m_pLogger)
            m_pLogger = new (std::nothrow)RPM_Logger();
    }

    // still not created?
    if (!m_pLogger)
        M_THROW_EXCEPTION("Could not create the Logger unique instance");

    return m_pLogger;
}
//---------------------------------------------------------------------------
void RPM_Logger::Clear()
{
    m_Log.clear();
}
//---------------------------------------------------------------------------
void RPM_Logger::Open(const IHeader& header)
{
    Clear();

    // get the locale. NOTE double call is required because the locale will returns an empty value
    std::setlocale(LC_ALL, "");
    const char*        pLocale       = std::setlocale(LC_ALL, "");
    const std::wstring currentLocale = pLocale ? RPM_StringHelper::Utf8ToUtf16(pLocale) : L"Unknown";

    std::wostringstream sstr;
    sstr << L"---------------------------------------------------------------------------" << M_WEOL;
    sstr << header.m_Name << L" - v" << header.m_Version.ToWStr()                          << M_WEOL;
    sstr << L"---------------------------------------------------------------------------" << M_WEOL;
    sstr << L"Locale          - "          << currentLocale       << M_WEOL;
    sstr << L"Screen          - width - "  << header.m_ScreenWidth
                        << L" - height - " << header.m_ScreenHeight
                        << L" - DPI - "    << header.m_ScreenDPI  << M_WEOL;
    sstr << L"Start date time - "          << GetTimeStamp(false) << M_WEOL;
    sstr << M_WEOL;
    sstr << L"Log start" << M_WEOL;

    m_Log = sstr.str();
}
//---------------------------------------------------------------------------
void RPM_Logger::Close()
{
    std::wostringstream sstr;
    sstr << L"Log end." << M_WEOL;

    m_Log += sstr.str();
}
//---------------------------------------------------------------------------
std::wstring RPM_Logger::Get() const
{
    return m_Log;
}
//---------------------------------------------------------------------------
std::wstring RPM_Logger::GetTimeStamp(bool timeOnly) const
{
    // get the current time
    std::time_t time;
    std::time(&time);

    // convert to date and time structure
    const std::tm* pDateTime = std::localtime(&time);

    if (timeOnly)
        return pDateTime ? RPM_StringHelper::Utf8ToUtf16(RPM_TimeHelper::TmToStr(*pDateTime, "%T", "")) : L"Unknown";

    return pDateTime ? RPM_StringHelper::Utf8ToUtf16(RPM_TimeHelper::TmToStr(*pDateTime, "%F %T", "")) : L"Unknown";
}
//---------------------------------------------------------------------------
std::wstring RPM_Logger::GetFileName(const std::wstring& appName) const
{
    return RPM_FileHelper::EscapeForbiddenChars(appName + L"_" + GetTimeStamp(false) + L".txt", L'\'');
}
//---------------------------------------------------------------------------
