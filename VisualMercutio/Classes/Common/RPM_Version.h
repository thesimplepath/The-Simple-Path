/****************************************************************************
 * ==> RPM_Version ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a version number management class                 *
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
#include <string>

/**
* Version number management class
*@author Jean-Milost Reymond
*/
class RPM_Version
{
    public:
        RPM_Version();

        /**
        * Constructor
        *@param major - major version
        *@param minor - minor version
        *@param release - release version
        *@param build - build version
        */
        RPM_Version(std::uint32_t major, std::uint32_t minor, std::uint32_t release, std::uint32_t build);

        virtual ~RPM_Version();

        /**
        * Gets version major component
        *@return major version
        */
        virtual std::uint32_t GetMajor() const;

        /**
        * Sets version major component
        *@param value - major version
        */
        virtual void SetMajor(std::uint32_t value);

        /**
        * Gets version minor component
        *@return version minor component
        */
        virtual std::uint32_t GetMinor() const;

        /**
        * Sets version minor component
        *@param value - version minor component
        */
        virtual void SetMinor(std::uint32_t value);

        /**
        * Gets version release component
        *@return version release component
        */
        virtual std::uint32_t GetRelease() const;

        /**
        * Sets version release component
        *@param value - version release component
        */
        virtual void SetRelease(std::uint32_t value);

        /**
        * Gets version build component
        *@return version build component
        */
        virtual std::uint32_t GetBuild() const;

        /**
        * Sets version build component
        *@param value - version build component
        */
        virtual void SetBuild(std::uint32_t value);

        /**
        * Gets version as string
        *@return version as string
        */
        virtual std::string  ToStr()  const;
        virtual std::wstring ToWStr() const;

    private:
        std::uint32_t m_Major   = 0;
        std::uint32_t m_Minor   = 0;
        std::uint32_t m_Release = 0;
        std::uint32_t m_Build   = 0;
};
