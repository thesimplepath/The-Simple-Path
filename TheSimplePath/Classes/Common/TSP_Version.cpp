/****************************************************************************
 * ==> TSP_Version ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a version number management class                 *
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

#include "TSP_Version.h"

// std
#include <sstream>

//---------------------------------------------------------------------------
// TSP_Version
//---------------------------------------------------------------------------
TSP_Version::TSP_Version()
{}
//---------------------------------------------------------------------------
TSP_Version::TSP_Version(std::uint32_t major, std::uint32_t minor, std::uint32_t release, std::uint32_t build)
{
    // set version
    SetMajor(major);
    SetMinor(minor);
    SetRelease(release);
    SetBuild(build);
}
//---------------------------------------------------------------------------
TSP_Version::~TSP_Version()
{}
//---------------------------------------------------------------------------
std::uint32_t TSP_Version::GetMajor() const
{
    return m_Major;
}
//---------------------------------------------------------------------------
void TSP_Version::SetMajor(std::uint32_t value)
{
    m_Major = value;
}
//---------------------------------------------------------------------------
std::uint32_t TSP_Version::GetMinor() const
{
    return m_Minor;
}
//---------------------------------------------------------------------------
void TSP_Version::SetMinor(std::uint32_t value)
{
    m_Minor = value;
}
//---------------------------------------------------------------------------
std::uint32_t TSP_Version::GetRelease() const
{
    return m_Release;
}
//---------------------------------------------------------------------------
void TSP_Version::SetRelease(std::uint32_t value)
{
    m_Release = value;
}
//---------------------------------------------------------------------------
std::uint32_t TSP_Version::GetBuild() const
{
    return m_Build;
}
//---------------------------------------------------------------------------
void TSP_Version::SetBuild(std::uint32_t value)
{
    m_Build = value;
}
//---------------------------------------------------------------------------
std::string TSP_Version::ToStr() const
{
    std::ostringstream sstr;

    // build version string
    sstr << m_Major << "." << m_Minor << "." << m_Release << "." << m_Build;

    return sstr.str();
}
//---------------------------------------------------------------------------
std::wstring TSP_Version::ToWStr() const
{
    std::wostringstream sstr;

    // build version string
    sstr << m_Major << L"." << m_Minor << L"." << m_Release << L"." << m_Build;

    return sstr.str();
}
//---------------------------------------------------------------------------
