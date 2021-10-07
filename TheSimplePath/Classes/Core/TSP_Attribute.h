/****************************************************************************
 * ==> TSP_Attribute -------------------------------------------------------*
 ****************************************************************************
 * Description:  Basic attribute which may be contained in an element       *
 * Contained in: Core                                                       *
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
#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

// common classes
#include "Common\TSP_Exception.h"
#include "Common\TSP_Logger.h"

/**
* Basic attribute which may be contained in an element
*@author Jean-Milost Reymond
*/
class TSP_Attribute
{
    public:
        /**
        * Attribute keys
        */
        enum class IEKey
        {
            IE_K_Unknown = 0
        };

        /**
        * Attribute value format type
        */
        enum class IEFormat
        {
            IE_Undefined = 0,
            IE_Bool,
            IE_Int8,
            IE_UInt8,
            IE_Int16,
            IE_UInt16,
            IE_Int32,
            IE_UInt32,
            IE_Int64,
            IE_UInt64,
            IE_Float,
            IE_Double,
            IE_String,
            IE_UnicodeString,
            IE_DateTime
        };

        /**
        * Constructor
        */
        TSP_Attribute();

        /**
        * Constructor
        *@param value - value for meta-data
        *@note Meta-data created with this constructor are strict
        */
        template<class T>
        inline TSP_Attribute(const T& value);

        virtual ~TSP_Attribute();

        /**
        * Copy operator
        *@param other - other attribute to copy from
        *@return this attribute
        */
        virtual inline TSP_Attribute& operator = (const TSP_Attribute& other);
        virtual inline TSP_Attribute& operator = (const char*          pOther);
        virtual inline TSP_Attribute& operator = (const wchar_t*       pOther);

        /**
        * Equality operator
        *@param other - other attribute to compare with
        *@return true if attributes are identical, otherwise false
        */
        virtual inline bool operator == (const TSP_Attribute& value)  const;
        virtual inline bool operator == (const char*          pOther) const;
        virtual inline bool operator == (const wchar_t*       pOther) const;

        /**
        * Not equality operator
        *@param other - other attribute to compare with
        *@return true if attributes are not identical, otherwise false
        */
        virtual inline bool operator != (const TSP_Attribute& value)  const;
        virtual inline bool operator != (const char*          pOther) const;
        virtual inline bool operator != (const wchar_t*       pOther) const;

        /**
        * Clears the attribute
        */
        virtual void Clear();

        /**
        * Sets the time format to use for conversions
        *@param timeFormat - new time format to use for conversions
        */
        virtual void SetTimeFormat(const std::string& timeFormat);

        /**
        * Gets the time format used for conversions
        *@return the time format used for conversions
        */
        virtual std::string GetTimeFormat() const;

        /**
        * Sets the attribute value
        *@param value - value to set
        */
        virtual void Set(bool                value);
        virtual void Set(std::int8_t         value);
        virtual void Set(std::uint8_t        value);
        virtual void Set(std::int16_t        value);
        virtual void Set(std::uint16_t       value);
        virtual void Set(std::int32_t        value);
        virtual void Set(std::uint32_t       value);
        virtual void Set(std::int64_t        value);
        virtual void Set(std::uint64_t       value);
        virtual void Set(float               value);
        virtual void Set(double              value);
        virtual void Set(const std::string&  value);
        virtual void Set(const std::wstring& value);
        virtual void Set(const char*         pDefVal);
        virtual void Set(const wchar_t*      pDefVal);
        virtual void Set(const std::tm&      value);

        /**
        * Gets the attribute value
        *@return the attribute value
        */
        template<class T>
        T Get() const;

        /**
        * Gets the attribute value
        *@param defVal - default value to return in case the internal type conversion fails
        *@return the attribute value
        */
        virtual bool          Get(bool                defVal)  const;
        virtual std::int8_t   Get(std::int8_t         defVal)  const;
        virtual std::uint8_t  Get(std::uint8_t        defVal)  const;
        virtual std::int16_t  Get(std::int16_t        defVal)  const;
        virtual std::uint16_t Get(std::uint16_t       defVal)  const;
        virtual std::int32_t  Get(std::int32_t        defVal)  const;
        virtual std::uint32_t Get(std::uint32_t       defVal)  const;
        virtual std::int64_t  Get(std::int64_t        defVal)  const;
        virtual std::uint64_t Get(std::uint64_t       defVal)  const;
        virtual float         Get(float               defVal)  const;
        virtual double        Get(double              defVal)  const;
        virtual std::string   Get(const std::string&  defVal)  const;
        virtual std::wstring  Get(const std::wstring& defVal)  const;
        virtual std::string   Get(const char*         pDefVal) const;
        virtual std::wstring  Get(const wchar_t*      pDefVal) const;
        virtual std::tm       Get(const std::tm&      defVal)  const;

        /**
        * Gets the attribute value size in bytes
        *@return the attribute value size in bytes
        */
        virtual std::size_t GetSize() const;

    private:
        std::string m_TimeFormat = "%F %T";
        void*       m_pData      = nullptr;
        IEFormat    m_Format     = IEFormat::IE_Undefined;

        /**
        * Checks if an attribute equals another one
        *@param other - other attribute to compare with
        *@return true if the attribute equals the other, otherwise false
        */
        template<class T>
        bool Equals(const TSP_Attribute& other) const;

        /**
        * Checks if an attribute differs from another one
        *@param other - other attribute to compare with
        *@return true if the attribute differs from the other, otherwise false
        */
        template<class T>
        bool Differs(const TSP_Attribute& other) const;
};

/**
* Attribute list
*/
typedef std::vector<TSP_Attribute*> TSP_Attributes;

//---------------------------------------------------------------------------
// TSP_Attribute
//---------------------------------------------------------------------------
template<class T>
TSP_Attribute::TSP_Attribute(const T& value)
{
    Set(value);
}
//---------------------------------------------------------------------------
TSP_Attribute& TSP_Attribute::operator = (const TSP_Attribute& other)
{
    switch (other.m_Format)
    {
        case IEFormat::IE_Bool:          Set(other.Get<bool>());          break;
        case IEFormat::IE_Int8:          Set(other.Get<std::int8_t>());   break;
        case IEFormat::IE_UInt8:         Set(other.Get<std::uint8_t>());  break;
        case IEFormat::IE_Int16:         Set(other.Get<std::int16_t>());  break;
        case IEFormat::IE_UInt16:        Set(other.Get<std::uint16_t>()); break;
        case IEFormat::IE_Int32:         Set(other.Get<std::int32_t>());  break;
        case IEFormat::IE_UInt32:        Set(other.Get<std::uint32_t>()); break;
        case IEFormat::IE_Int64:         Set(other.Get<std::int64_t>());  break;
        case IEFormat::IE_UInt64:        Set(other.Get<std::uint64_t>()); break;
        case IEFormat::IE_Float:         Set(other.Get<float>());         break;
        case IEFormat::IE_Double:        Set(other.Get<double>());        break;
        case IEFormat::IE_String:        Set(other.Get<std::string>());   break;
        case IEFormat::IE_UnicodeString: Set(other.Get<std::wstring>());  break;
        default:                         M_THROW_EXCEPTION("Unknown or undefined format - " + std::to_string((int)other.m_Format));
    }

    return *this;
}
//---------------------------------------------------------------------------
TSP_Attribute& TSP_Attribute::operator = (const char* pOther)
{
    Set(std::string(pOther));
    return *this;
}
//---------------------------------------------------------------------------
TSP_Attribute& TSP_Attribute::operator = (const wchar_t* pOther)
{
    Set(std::wstring(pOther));
    return *this;
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator == (const TSP_Attribute& other) const
{
    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return Equals<bool>(other);
        case IEFormat::IE_Int8:          return Equals<std::int8_t>(other);
        case IEFormat::IE_UInt8:         return Equals<std::uint8_t>(other);
        case IEFormat::IE_Int16:         return Equals<std::int16_t>(other);
        case IEFormat::IE_UInt16:        return Equals<std::uint16_t>(other);
        case IEFormat::IE_Int32:         return Equals<std::int32_t>(other);
        case IEFormat::IE_UInt32:        return Equals<std::uint32_t>(other);
        case IEFormat::IE_Int64:         return Equals<std::int64_t>(other);
        case IEFormat::IE_UInt64:        return Equals<std::uint64_t>(other);
        case IEFormat::IE_Float:         return Equals<float>(other);
        case IEFormat::IE_Double:        return Equals<double>(other);
        case IEFormat::IE_String:        return Equals<std::string>(other);
        case IEFormat::IE_UnicodeString: return Equals<std::wstring>(other);
    }

    return false;
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator == (const char* pOther) const
{
    return Equals<std::string>(std::string(pOther));
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator == (const wchar_t* pOther) const
{
    return Equals<std::wstring>(std::wstring(pOther));
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator != (const TSP_Attribute& other) const
{
    switch (m_Format)
    {
        case IEFormat::IE_Bool:          return Differs<bool>(other);
        case IEFormat::IE_Int8:          return Differs<std::int8_t>(other);
        case IEFormat::IE_UInt8:         return Differs<std::uint8_t>(other);
        case IEFormat::IE_Int16:         return Differs<std::int16_t>(other);
        case IEFormat::IE_UInt16:        return Differs<std::uint16_t>(other);
        case IEFormat::IE_Int32:         return Differs<std::int32_t>(other);
        case IEFormat::IE_UInt32:        return Differs<std::uint32_t>(other);
        case IEFormat::IE_Int64:         return Differs<std::int64_t>(other);
        case IEFormat::IE_UInt64:        return Differs<std::uint64_t>(other);
        case IEFormat::IE_Float:         return Differs<float>(other);
        case IEFormat::IE_Double:        return Differs<double>(other);
        case IEFormat::IE_String:        return Differs<std::string>(other);
        case IEFormat::IE_UnicodeString: return Differs<std::wstring>(other);
    }

    return false;
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator != (const char* pOther) const
{
    return Differs<std::string>(std::string(pOther));
}
//---------------------------------------------------------------------------
bool TSP_Attribute::operator != (const wchar_t* pOther) const
{
    return Differs<std::wstring>(std::wstring(pOther));
}
//---------------------------------------------------------------------------
template <class T>
T TSP_Attribute::Get() const
{
    T value = T();

    return Get(value);
}
//---------------------------------------------------------------------------
template<class T>
bool TSP_Attribute::Equals(const TSP_Attribute& other) const
{
    T value1 = T();
    T value2 = T();

    Get(value1);
    other.Get(value2);

    return (value1 == value2);
}
//---------------------------------------------------------------------------
template<class T>
bool TSP_Attribute::Differs(const TSP_Attribute& other) const
{
    T value1 = T();
    T value2 = T();

    Get(value1);
    other.Get(value2);

    return (value1 != value2);
}
//---------------------------------------------------------------------------
