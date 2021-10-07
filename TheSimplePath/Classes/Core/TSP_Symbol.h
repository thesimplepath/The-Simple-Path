/****************************************************************************
 * ==> TSP_Symbol ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Basic symbol                                               *
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
#include <vector>

// core classes
#include "TSP_Element.h"

/**
* Basic symbol
*@author Jean-Milost Reymond
*/
class TSP_Symbol : public TSP_Element
{
    public:
        TSP_Symbol();
        virtual ~TSP_Symbol();

        /**
        * Gets the symbol name
        *@return the symbol name
        */
        virtual std::wstring GetSymbolName() const = 0;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        *@return true on success, otherwise false
        */
        virtual bool SetSymbolName(const std::wstring& value) = 0;

        /**
        * Gets the symbol comments
        *@return the symbol comments
        */
        virtual std::wstring GetSymbolComments() const = 0;

        /**
        * Sets the symbol comments
        *@param value - the symbol comments
        *@return true on success, otherwise false
        */
        virtual bool SetSymbolComments(const std::wstring& value) = 0;

        /**
        * Gets the symbol reference number
        *@return the symbol reference number
        */
        virtual std::int32_t GetSymbolReferenceNumber() const = 0;

        /**
        * Sets the symbol reference number
        *@param value - the symbol reference number
        *@return true on success, otherwise false
        */
        virtual bool SetSymbolReferenceNumber(std::int32_t value) = 0;

    private:
        std::wstring m_Name;
        std::wstring m_Comments;
        std::int32_t m_RefNb = 0;
};
