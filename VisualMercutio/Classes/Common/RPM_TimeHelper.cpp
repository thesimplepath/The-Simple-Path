/****************************************************************************
 * ==> RPM_TimeHelper ------------------------------------------------------*
 ****************************************************************************
 * Description:  Helper class for date and time                             *
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

#include "RPM_TimeHelper.h"

// common classes
#include "RPM_StringHelper.h"

// std
#include <iomanip>
#include <iostream>
#include <sstream>

//---------------------------------------------------------------------------
// RPM_TimeHelper
//---------------------------------------------------------------------------
std::string RPM_TimeHelper::UTCTimeToIso8601(std::time_t time, const std::string& localeToUse)
{
    return RPM_TimeHelper::UTCTimeToStr(time, "%F %T", localeToUse);
}
//---------------------------------------------------------------------------
std::string RPM_TimeHelper::LocalTimeToIso8601(std::time_t time, const std::string& localeToUse)
{
    return RPM_TimeHelper::LocalTimeToStr(time, "%F %T", localeToUse);
}
//---------------------------------------------------------------------------
std::time_t RPM_TimeHelper::Iso8601ToTime(const std::string& str, const std::string& localeToUse)
{
    return StrToTime(str, "%Y-%b-%d %H:%M:%S", localeToUse);
}
//---------------------------------------------------------------------------
std::string RPM_TimeHelper::UTCTimeToStr(std::time_t time, const std::string& format, const std::string& localeToUse)
{
    const std::tm* pUTCTime = std::gmtime(&time);

    if (pUTCTime)
        return TmToStr(*pUTCTime, format, "");

    return "";
}
//---------------------------------------------------------------------------
std::string RPM_TimeHelper::LocalTimeToStr(std::time_t time, const std::string& format, const std::string& localeToUse)
{
    const std::tm* pLocalTime = std::localtime(&time);

    if (pLocalTime)
        return TmToStr(*pLocalTime, format, localeToUse);

    return "";
}
//---------------------------------------------------------------------------
std::time_t RPM_TimeHelper::StrToTime(const std::string& str, const std::string& format, const std::string& localeToUse)
{
    std::tm dateTime = StrToTm(str, format, localeToUse);
    return std::mktime(&dateTime);
}
//---------------------------------------------------------------------------
std::string RPM_TimeHelper::TmToStr(const std::tm& dateTime, const std::string& format, const std::string& localeToUse)
{
    std::ostringstream sstr;
    sstr.imbue(std::locale(localeToUse.c_str()));
    sstr << std::put_time(&dateTime, format.c_str());
    return sstr.str();
}
//---------------------------------------------------------------------------
std::tm RPM_TimeHelper::StrToTm(const std::string& str, const std::string& format, const std::string& localeToUse)
{
    std::tm dateTime = {};

    std::istringstream ss(str.c_str());
    ss.imbue(std::locale(localeToUse.c_str()));
    ss >> std::get_time(&dateTime, format.c_str());

    if (ss.fail())
        return std::tm() = {};

    return dateTime;
}
//---------------------------------------------------------------------------
