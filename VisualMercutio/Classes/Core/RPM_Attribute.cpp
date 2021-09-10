/****************************************************************************
 * ==> RPM_Attribute -------------------------------------------------------*
 ****************************************************************************
 * Description:  Basic attribute which may be contained in an element       *
 * Contained in: Core                                                       *
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

#include "RPM_Attribute.h"

// std
#include <iomanip>
#include <sstream>

// common classes
#include "Common\RPM_StringHelper.h"
#include "Common\RPM_TimeHelper.h"
#include "Common\RPM_Logger.h"

//---------------------------------------------------------------------------
// Global macros
//---------------------------------------------------------------------------
#define M_Safe_Conversion(conversion)\
try\
{\
    return conversion;\
}\
catch (...)\
{\
    M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");\
    return defVal;\
}\
//---------------------------------------------------------------------------
#define M_Safe_Conversion_Ptr(conversion)\
try\
{\
    return conversion;\
}\
catch (...)\
{\
    M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");\
    return pDefVal;\
}\
//---------------------------------------------------------------------------
// RPM_Attribute
//---------------------------------------------------------------------------
RPM_Attribute::RPM_Attribute()
{}
//---------------------------------------------------------------------------
RPM_Attribute::~RPM_Attribute()
{
    if (m_pData)
        delete m_pData;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Clear()
{
    if (m_pData)
        delete m_pData;

    m_pData  = nullptr;
    m_Format = IEFormat::IE_Undefined;
}
//---------------------------------------------------------------------------
void RPM_Attribute::SetTimeFormat(const std::string& timeFormat)
{
    m_TimeFormat = timeFormat;
}
//---------------------------------------------------------------------------
std::string RPM_Attribute::GetTimeFormat() const
{
    return m_TimeFormat;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(bool value)
{
    Clear();

    m_pData  = new bool(value);
    m_Format = IEFormat::IE_Bool;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::int8_t value)
{
    Clear();

    m_pData  = new std::int8_t(value);
    m_Format = IEFormat::IE_Int8;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::uint8_t value)
{
    Clear();

    m_pData  = new std::uint8_t(value);
    m_Format = IEFormat::IE_UInt8;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::int16_t value)
{
    Clear();

    m_pData  = new std::int16_t(value);
    m_Format = IEFormat::IE_Int16;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::uint16_t value)
{
    Clear();

    m_pData = new std::uint16_t(value);
    m_Format = IEFormat::IE_UInt16;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::int32_t value)
{
    Clear();

    m_pData  = new std::int32_t(value);
    m_Format = IEFormat::IE_Int32;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::uint32_t value)
{
    Clear();

    m_pData  = new std::uint32_t(value);
    m_Format = IEFormat::IE_UInt32;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::int64_t value)
{
    Clear();

    m_pData  = new std::int64_t(value);
    m_Format = IEFormat::IE_Int64;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(std::uint64_t value)
{
    Clear();

    m_pData  = new std::uint64_t(value);
    m_Format = IEFormat::IE_UInt64;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(float value)
{
    Clear();

    m_pData  = new float(value);
    m_Format = IEFormat::IE_Float;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(double value)
{
    Clear();

    m_pData  = new double(value);
    m_Format = IEFormat::IE_Double;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(const std::string& value)
{
    Clear();

    m_pData  = new std::string(value);
    m_Format = IEFormat::IE_String;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(const std::wstring& value)
{
    Clear();

    m_pData  = new std::wstring(value);
    m_Format = IEFormat::IE_UnicodeString;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(const char* pDefVal)
{
    Clear();

    m_pData  = new std::string(pDefVal);
    m_Format = IEFormat::IE_String;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(const wchar_t* pDefVal)
{
    Clear();

    m_pData  = new std::wstring(pDefVal);
    m_Format = IEFormat::IE_UnicodeString;
}
//---------------------------------------------------------------------------
void RPM_Attribute::Set(const std::tm& value)
{
    Clear();

    m_pData  = new std::tm(value);
    m_Format = IEFormat::IE_DateTime;
}
//---------------------------------------------------------------------------
bool RPM_Attribute::Get(bool defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return *static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return *static_cast<std::int8_t*>  (m_pData) ? true : false;
        case IEFormat::IE_UInt8:         return *static_cast<std::uint8_t*> (m_pData) ? true : false;
        case IEFormat::IE_Int16:         return *static_cast<std::int16_t*> (m_pData) ? true : false;
        case IEFormat::IE_UInt16:        return *static_cast<std::uint16_t*>(m_pData) ? true : false;
        case IEFormat::IE_Int32:         return *static_cast<std::int32_t*> (m_pData) ? true : false;
        case IEFormat::IE_UInt32:        return *static_cast<std::uint32_t*>(m_pData) ? true : false;
        case IEFormat::IE_Int64:         return *static_cast<std::int64_t*> (m_pData) ? true : false;
        case IEFormat::IE_UInt64:        return *static_cast<std::uint64_t*>(m_pData) ? true : false;
        case IEFormat::IE_Float:         return *static_cast<float*>        (m_pData) ? true : false;
        case IEFormat::IE_Double:        return *static_cast<double*>       (m_pData) ? true : false;
        case IEFormat::IE_String:        return RPM_StringHelper::StrToBool(*static_cast<std::string*> (m_pData));
        case IEFormat::IE_UnicodeString: return RPM_StringHelper::StrToBool(*static_cast<std::wstring*>(m_pData));
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::int8_t RPM_Attribute::Get(std::int8_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::int8_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return              *static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::int8_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::int8_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::int8_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::int8_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::int8_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::int8_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::int8_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::int8_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::int8_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion((std::int8_t)std::stoi(*static_cast<std::string*> (m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion((std::int8_t)std::stoi(*static_cast<std::wstring*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint8_t RPM_Attribute::Get(std::uint8_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::uint8_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::uint8_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return               *static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::uint8_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::uint8_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::uint8_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::uint8_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::uint8_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::uint8_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::uint8_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::uint8_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion((std::uint8_t)std::stoul(*static_cast<std::string*> (m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion((std::uint8_t)std::stoul(*static_cast<std::wstring*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::int16_t RPM_Attribute::Get(std::int16_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::int16_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::int16_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::int16_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return               *static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::int16_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::int16_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::int16_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::int16_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::int16_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::int16_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::int16_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion((std::int16_t)std::stoi(*static_cast<std::string*> (m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion((std::int16_t)std::stoi(*static_cast<std::wstring*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint16_t RPM_Attribute::Get(std::uint16_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::uint16_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::uint16_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::uint16_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::uint16_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return                *static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::uint16_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::uint16_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::uint16_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::uint16_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::uint16_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::uint16_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion((std::uint16_t)std::stoul(*static_cast<std::string*> (m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion((std::uint16_t)std::stoul(*static_cast<std::wstring*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::int32_t RPM_Attribute::Get(std::int32_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::int32_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::int32_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::int32_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::int32_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::int32_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return               *static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::int32_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::int32_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::int32_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::int32_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::int32_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stoi(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stoi(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((std::int32_t)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint32_t RPM_Attribute::Get(std::uint32_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::uint32_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::uint32_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::uint32_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::uint32_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::uint32_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::uint32_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return                *static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::uint32_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::uint32_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::uint32_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::uint32_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stoul(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stoul(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((std::uint32_t)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::int64_t RPM_Attribute::Get(std::int64_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::int64_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::int64_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::int64_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::int64_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::int64_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::int64_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::int64_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return               *static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (std::int64_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::int64_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::int64_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stoll(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stoll(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((std::int64_t)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint64_t RPM_Attribute::Get(std::uint64_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (std::uint64_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (std::uint64_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (std::uint64_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (std::uint64_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (std::uint64_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (std::uint64_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (std::uint64_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (std::uint64_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return                *static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (std::uint64_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (std::uint64_t)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stoull(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stoull(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((std::uint64_t)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
float RPM_Attribute::Get(float defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (float)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (float)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (float)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (float)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (float)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (float)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (float)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (float)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (float)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return        *static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return (float)*static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stof(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stof(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((float)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
double RPM_Attribute::Get(double defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return (double)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:          return (double)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:         return (double)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:         return (double)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16:        return (double)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:         return (double)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32:        return (double)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:         return (double)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64:        return (double)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:         return (double)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double:        return         *static_cast<double*>       (m_pData);
        case IEFormat::IE_String:        M_Safe_Conversion(std::stod(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(std::stod(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion((double)std::mktime(static_cast<std::tm*>(m_pData)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::string RPM_Attribute::Get(const std::string& defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return RPM_StringHelper::BoolToStr(*static_cast<bool*>(m_pData));
        case IEFormat::IE_Int8:          M_Safe_Conversion(std::to_string(*static_cast<std::int8_t*>  (m_pData)))
        case IEFormat::IE_UInt8:         M_Safe_Conversion(std::to_string(*static_cast<std::uint8_t*> (m_pData)))
        case IEFormat::IE_Int16:         M_Safe_Conversion(std::to_string(*static_cast<std::int16_t*> (m_pData)))
        case IEFormat::IE_UInt16:        M_Safe_Conversion(std::to_string(*static_cast<std::uint16_t*>(m_pData)))
        case IEFormat::IE_Int32:         M_Safe_Conversion(std::to_string(*static_cast<std::int32_t*> (m_pData)))
        case IEFormat::IE_UInt32:        M_Safe_Conversion(std::to_string(*static_cast<std::uint32_t*>(m_pData)))
        case IEFormat::IE_Int64:         M_Safe_Conversion(std::to_string(*static_cast<std::int64_t*> (m_pData)))
        case IEFormat::IE_UInt64:        M_Safe_Conversion(std::to_string(*static_cast<std::uint64_t*>(m_pData)))
        case IEFormat::IE_Float:         M_Safe_Conversion(std::to_string(*static_cast<float*>(m_pData)))
        case IEFormat::IE_Double:        M_Safe_Conversion(std::to_string(*static_cast<double*>(m_pData)))
        case IEFormat::IE_String:        M_Safe_Conversion(*static_cast<std::string*>(m_pData))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(RPM_StringHelper::Utf16ToUtf8(*static_cast<std::wstring*>(m_pData)))
        case IEFormat::IE_DateTime:      M_Safe_Conversion(RPM_TimeHelper::TmToStr(*static_cast<std::tm*>(m_pData), m_TimeFormat))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::wstring RPM_Attribute::Get(const std::wstring& defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return RPM_StringHelper::BoolToWStr(*static_cast<bool*>(m_pData));
        case IEFormat::IE_Int8:          M_Safe_Conversion(std::to_wstring(*static_cast<std::int8_t*>  (m_pData)))
        case IEFormat::IE_UInt8:         M_Safe_Conversion(std::to_wstring(*static_cast<std::uint8_t*> (m_pData)))
        case IEFormat::IE_Int16:         M_Safe_Conversion(std::to_wstring(*static_cast<std::int16_t*> (m_pData)))
        case IEFormat::IE_UInt16:        M_Safe_Conversion(std::to_wstring(*static_cast<std::uint16_t*>(m_pData)))
        case IEFormat::IE_Int32:         M_Safe_Conversion(std::to_wstring(*static_cast<std::int32_t*> (m_pData)))
        case IEFormat::IE_UInt32:        M_Safe_Conversion(std::to_wstring(*static_cast<std::uint32_t*>(m_pData)))
        case IEFormat::IE_Int64:         M_Safe_Conversion(std::to_wstring(*static_cast<std::int64_t*> (m_pData)))
        case IEFormat::IE_UInt64:        M_Safe_Conversion(std::to_wstring(*static_cast<std::uint64_t*>(m_pData)))
        case IEFormat::IE_Float:         M_Safe_Conversion(std::to_wstring(*static_cast<float*>(m_pData)))
        case IEFormat::IE_Double:        M_Safe_Conversion(std::to_wstring(*static_cast<double*>(m_pData)))
        case IEFormat::IE_String:        M_Safe_Conversion(RPM_StringHelper::Utf8ToUtf16(*static_cast<std::string*>(m_pData)))
        case IEFormat::IE_UnicodeString: return *static_cast<std::wstring*>(m_pData);
        case IEFormat::IE_DateTime:      M_Safe_Conversion(RPM_StringHelper::Utf8ToUtf16(RPM_TimeHelper::TmToStr(*static_cast<std::tm*>(m_pData), m_TimeFormat)))
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::string RPM_Attribute::Get(const char* pDefVal) const
{
    if (!m_pData)
        return pDefVal;

    return Get(std::string(pDefVal));
}
//---------------------------------------------------------------------------
std::wstring RPM_Attribute::Get(const wchar_t* pDefVal) const
{
    if (!m_pData)
        return pDefVal;

    return Get(std::wstring(pDefVal));
}
//---------------------------------------------------------------------------
std::tm RPM_Attribute::Get(const std::tm& defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Int8:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::int8_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_UInt8:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::uint8_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_Int16:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::int16_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_UInt16:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::uint16_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_Int32:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::int32_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_UInt32:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::uint32_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_Int64:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::int64_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_UInt64:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<std::uint64_t*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_Float:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<float*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_Double:
            try
            {
                const std::time_t value     = (std::time_t)(*static_cast<double*>(m_pData));
                      std::tm*    pDateTime = std::gmtime(&value);

                if (pDateTime)
                    return *pDateTime;

                return defVal;
            }
            catch (...)
            {
                M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Conversion failed");
                return defVal;
            }

        case IEFormat::IE_String:        M_Safe_Conversion(RPM_TimeHelper::StrToTm(*static_cast<std::string*>(m_pData), m_TimeFormat))
        case IEFormat::IE_UnicodeString: M_Safe_Conversion(RPM_TimeHelper::StrToTm(RPM_StringHelper::Utf16ToUtf8(*static_cast<std::wstring*>(m_pData)), m_TimeFormat))
        case IEFormat::IE_DateTime:      return *static_cast<std::tm*>(m_pData);
        default:                         return defVal;
    }
}
//---------------------------------------------------------------------------
std::size_t RPM_Attribute::GetSize() const
{
    if (!m_pData)
        return 0;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return sizeof(bool);
        case IEFormat::IE_Int8:          return sizeof(std::int8_t);
        case IEFormat::IE_UInt8:         return sizeof(std::uint8_t);
        case IEFormat::IE_Int16:         return sizeof(std::int16_t);
        case IEFormat::IE_UInt16:        return sizeof(std::uint16_t);
        case IEFormat::IE_Int32:         return sizeof(std::int32_t);
        case IEFormat::IE_UInt32:        return sizeof(std::uint32_t);
        case IEFormat::IE_Int64:         return sizeof(std::int64_t);
        case IEFormat::IE_UInt64:        return sizeof(std::uint64_t);
        case IEFormat::IE_Float:         return sizeof(float);
        case IEFormat::IE_Double:        return sizeof(double);
        case IEFormat::IE_String:        return                   (*static_cast<std::string*> (m_pData)).length();
        case IEFormat::IE_UnicodeString: return sizeof(wchar_t) * (*static_cast<std::wstring*>(m_pData)).length();
        case IEFormat::IE_DateTime:      return sizeof(std::tm);
        default:                         return 0;
    }
}
//---------------------------------------------------------------------------
