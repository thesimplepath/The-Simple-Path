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

#pragma once

// std
#include <ctime>
#include <string>

/**
* Helper class for date and time
*@author Jean-Milost Reymond
*/
class RPM_TimeHelper
{
    public:
        /**
        * Converts an UTC date and time value to an ISO 8601 string
        *@param time - UTC date and time value to convert
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return date and time as ISO 8601 string
        */
        static std::string UTCTimeToIso8601(std::time_t time, const std::string& localeToUse = "");

        /**
        * Converts a local date and time value to an ISO 8601 string
        *@param time - local date and time value to convert
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return date and time as ISO 8601 string
        */
        static std::string LocalTimeToIso8601(std::time_t time, const std::string& localeToUse = "");

        /**
        * Converts an ISO 8601 string to a date and time value
        *@param str - ISO 8601 string to convert
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return date and time value
        */
        static std::time_t Iso8601ToTime(const std::string& str, const std::string& localeToUse = "");

        /**
        * Converts an UTC date and time value to a string
        *@param time - UTC date and time value to convert
        *@param format - format to use for the conversion
        *@return string formatted date and time
        */
        static std::string UTCTimeToStr(std::time_t time, const std::string& format, const std::string& localeToUse = "");

        /**
        * Converts a local date and time value to a string
        *@param time - local date and time value to convert
        *@param format - format to use for the conversion
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return string formatted date and time
        */
        static std::string LocalTimeToStr(std::time_t time, const std::string& format, const std::string& localeToUse = "");

        /**
        * Converts a string to a date and time value
        *@param str - string to convert
        *@param format - format to use for the conversion
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return date and time value
        */
        static std::time_t StrToTime(const std::string& str, const std::string& format, const std::string& localeToUse = "");

        /**
        * Converts a date and time structure to a string
        *@param dateTime - date and time structure to convert
        *@param format - format to use for the conversion
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return string formatted date and time
        */
        static std::string TmToStr(const std::tm& dateTime, const std::string& format, const std::string& localeToUse = "");

        /**
        * Converts a string to a date and time value
        *@param str - string to convert
        *@param format - format to use for the conversion
        *@param localeToUse - locale to use for the conversion, default if empty
        *@return date and time structure
        */
        static std::tm StrToTm(const std::string& str, const std::string& format, const std::string& localeToUse = "");
};
