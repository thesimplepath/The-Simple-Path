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

//---------------------------------------------------------------------------
// RPM_Attribute
//---------------------------------------------------------------------------
RPM_Attribute::RPM_Attribute() :
    RPM_Item()
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
    m_Size   = 0;
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
        case IEFormat::IE_String:        return RPM_StringHelper::StrToBool(*static_cast<std::string*>(m_pData));
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
        case IEFormat::IE_Bool:   return (std::int8_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return              *static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::int8_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::int8_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::int8_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::int8_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::int8_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::int8_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::int8_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::int8_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::int8_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::int8_t result = defVal;

            try
            {
                result = (std::int8_t)std::stoi(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::int8_t result = defVal;

            try
            {
                result = (std::int8_t)std::stoi(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        default:
            return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint8_t RPM_Attribute::Get(std::uint8_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::uint8_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::uint8_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return               *static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::uint8_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::uint8_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::uint8_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::uint8_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::uint8_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::uint8_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::uint8_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::uint8_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::uint8_t result = defVal;

            try
            {
                result = (std::uint8_t)std::stoul(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::uint8_t result = defVal;

            try
            {
                result = (std::uint8_t)std::stoul(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        default:
            return defVal;
    }
}
//---------------------------------------------------------------------------
std::int16_t RPM_Attribute::Get(std::int16_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::int16_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::int16_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::int16_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return               *static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::int16_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::int16_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::int16_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::int16_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::int16_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::int16_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::int16_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::int16_t result = defVal;

            try
            {
                result = (std::int16_t)std::stoi(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::int16_t result = defVal;

            try
            {
                result = (std::int16_t)std::stoi(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        default:
            return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint16_t RPM_Attribute::Get(std::uint16_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::uint16_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::uint16_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::uint16_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::uint16_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return                *static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::uint16_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::uint16_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::uint16_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::uint16_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::uint16_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::uint16_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::uint16_t result = defVal;

            try
            {
                result = (std::uint16_t)std::stoul(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::uint16_t result = defVal;

            try
            {
                result = (std::uint16_t)std::stoul(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        default:
            return defVal;
    }
}
//---------------------------------------------------------------------------
std::int32_t RPM_Attribute::Get(std::int32_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::int32_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::int32_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::int32_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::int32_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::int32_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return               *static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::int32_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::int32_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::int32_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::int32_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::int32_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::int32_t result = defVal;

            try
            {
                result = std::stoi(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::int32_t result = defVal;

            try
            {
                result = std::stoi(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (std::int32_t)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint32_t RPM_Attribute::Get(std::uint32_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::uint32_t) * static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::uint32_t) * static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::uint32_t) * static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::uint32_t) * static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::uint32_t) * static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::uint32_t) *static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return               * static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::uint32_t) * static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::uint32_t) * static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::uint32_t) * static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::uint32_t) * static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::uint32_t result = defVal;

            try
            {
                result = std::stoul(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::uint32_t result = defVal;

            try
            {
                result = std::stoul(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (std::uint32_t)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
std::int64_t RPM_Attribute::Get(std::int64_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::int64_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::int64_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::int64_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::int64_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::int64_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::int64_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::int64_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return               *static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (std::int64_t)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::int64_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::int64_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::int64_t result = defVal;

            try
            {
                result = std::stoll(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::int64_t result = defVal;

            try
            {
                result = std::stoll(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (std::int64_t)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
std::uint64_t RPM_Attribute::Get(std::uint64_t defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (std::uint64_t)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (std::uint64_t)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (std::uint64_t)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (std::uint64_t)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (std::uint64_t)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (std::uint64_t)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (std::uint64_t)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (std::uint64_t)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return                *static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (std::uint64_t)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (std::uint64_t)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            std::uint64_t result = defVal;

            try
            {
                result = std::stoull(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            std::uint64_t result = defVal;

            try
            {
                result = std::stoull(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (std::uint64_t)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
float RPM_Attribute::Get(float defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (float)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (float)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (float)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (float)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (float)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (float)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (float)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (float)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (float)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return        *static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return (float)*static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            float result = defVal;

            try
            {
                result = std::stof(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            float result = defVal;

            try
            {
                result = std::stof(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (float)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
double RPM_Attribute::Get(double defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Bool:   return (double)*static_cast<bool*>         (m_pData);
        case IEFormat::IE_Int8:   return (double)*static_cast<std::int8_t*>  (m_pData);
        case IEFormat::IE_UInt8:  return (double)*static_cast<std::uint8_t*> (m_pData);
        case IEFormat::IE_Int16:  return (double)*static_cast<std::int16_t*> (m_pData);
        case IEFormat::IE_UInt16: return (double)*static_cast<std::uint16_t*>(m_pData);
        case IEFormat::IE_Int32:  return (double)*static_cast<std::int32_t*> (m_pData);
        case IEFormat::IE_UInt32: return (double)*static_cast<std::uint32_t*>(m_pData);
        case IEFormat::IE_Int64:  return (double)*static_cast<std::int64_t*> (m_pData);
        case IEFormat::IE_UInt64: return (double)*static_cast<std::uint64_t*>(m_pData);
        case IEFormat::IE_Float:  return (double)*static_cast<float*>        (m_pData);
        case IEFormat::IE_Double: return         *static_cast<double*>       (m_pData);

        case IEFormat::IE_String:
        {
            double result = defVal;

            try
            {
                result = std::stod(*static_cast<std::string*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_UnicodeString:
        {
            double result = defVal;

            try
            {
                result = std::stod(*static_cast<std::wstring*>(m_pData));
            }
            catch (std::exception& e)
            {
                return defVal;
            }

            return result;
        }

        case IEFormat::IE_DateTime: return (double)*static_cast<std::time_t*>(m_pData);
        default:                    return defVal;
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
        case IEFormat::IE_Int8:          return std::to_string(*static_cast<std::int8_t*>  (m_pData));
        case IEFormat::IE_UInt8:         return std::to_string(*static_cast<std::uint8_t*> (m_pData));
        case IEFormat::IE_Int16:         return std::to_string(*static_cast<std::int16_t*> (m_pData));
        case IEFormat::IE_UInt16:        return std::to_string(*static_cast<std::uint16_t*>(m_pData));
        case IEFormat::IE_Int32:         return std::to_string(*static_cast<std::int32_t*> (m_pData));
        case IEFormat::IE_UInt32:        return std::to_string(*static_cast<std::uint32_t*>(m_pData));
        case IEFormat::IE_Int64:         return std::to_string(*static_cast<std::int64_t*> (m_pData));
        case IEFormat::IE_UInt64:        return std::to_string(*static_cast<std::uint64_t*>(m_pData));
        case IEFormat::IE_Float:         return std::to_string(*static_cast<float*>        (m_pData));
        case IEFormat::IE_Double:        return std::to_string(*static_cast<double*>       (m_pData));
        case IEFormat::IE_String:        return                               *static_cast<std::string*> (m_pData);
        case IEFormat::IE_UnicodeString: return RPM_StringHelper::Utf16ToUtf8(*static_cast<std::wstring*>(m_pData));

        case IEFormat::IE_DateTime:
        {
            std::ostringstream sstr;
            sstr << std::put_time(std::localtime(static_cast<std::time_t*>(m_pData)), "%F %T.\n");
            return sstr.str();
        }

        default:
            return defVal;
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
        case IEFormat::IE_Int8:          return std::to_wstring(*static_cast<std::int8_t*>  (m_pData));
        case IEFormat::IE_UInt8:         return std::to_wstring(*static_cast<std::uint8_t*> (m_pData));
        case IEFormat::IE_Int16:         return std::to_wstring(*static_cast<std::int16_t*> (m_pData));
        case IEFormat::IE_UInt16:        return std::to_wstring(*static_cast<std::uint16_t*>(m_pData));
        case IEFormat::IE_Int32:         return std::to_wstring(*static_cast<std::int32_t*> (m_pData));
        case IEFormat::IE_UInt32:        return std::to_wstring(*static_cast<std::uint32_t*>(m_pData));
        case IEFormat::IE_Int64:         return std::to_wstring(*static_cast<std::int64_t*> (m_pData));
        case IEFormat::IE_UInt64:        return std::to_wstring(*static_cast<std::uint64_t*>(m_pData));
        case IEFormat::IE_Float:         return std::to_wstring(*static_cast<float*>        (m_pData));
        case IEFormat::IE_Double:        return std::to_wstring(*static_cast<double*>       (m_pData));
        case IEFormat::IE_String:        return RPM_StringHelper::Utf8ToUtf16(*static_cast<std::string*> (m_pData));
        case IEFormat::IE_UnicodeString: return                               *static_cast<std::wstring*>(m_pData);

        case IEFormat::IE_DateTime:
        {
            std::ostringstream sstr;
            sstr << std::put_time(static_cast<std::tm*>(m_pData), "%F %T.\n");
            return RPM_StringHelper::Utf8ToUtf16(sstr.str());
        }

        default:
            return defVal;
    }
}
//---------------------------------------------------------------------------
std::tm RPM_Attribute::Get(const std::tm& defVal) const
{
    if (!m_pData)
        return defVal;

    switch (m_Format)
    {
        case IEFormat::IE_Int8:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::int8_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_UInt8:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::uint8_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_Int16:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::int16_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_UInt16:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::uint16_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_Int32:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::int32_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_UInt32:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::uint32_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_Int64:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::int64_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_UInt64:
        {
            const std::time_t value     = (std::time_t)(*static_cast<std::uint64_t*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_Float:
        {
            const std::time_t value     = (std::time_t)(*static_cast<float*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_Double:
        {
            const std::time_t value     = (std::time_t)(*static_cast<double*>(m_pData));
                  std::tm*    pDateTime = std::gmtime(&value);

            if (pDateTime)
                return *pDateTime;

            return std::tm() = {};
        }

        case IEFormat::IE_String:
        {}

        case IEFormat::IE_UnicodeString:
        {}

        case IEFormat::IE_DateTime: return *static_cast<std::tm*>(m_pData);
        default:                    return defVal;
    }
}
//---------------------------------------------------------------------------
