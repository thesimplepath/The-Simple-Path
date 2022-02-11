/****************************************************************************
 * ==> TSP_Component -------------------------------------------------------*
 ****************************************************************************
 * Description:  Component (which may be inserted on a page)                *
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

// core classes
#include "TSP_Item.h"
#include "TSP_Attribute.h"

// class prototypes
class TSP_Page;

/**
* Component (which may be inserted on a page)
*@author Jean-Milost Reymond
*/
class TSP_Component : public TSP_Item
{
    public:
        /**
        * Constructor
        *@param pOwner - component owner
        */
        TSP_Component(TSP_Page* pOwner);

        /**
        * Constructor
        *@param title - component title
        *@param description - component description
        *@param comments - component comments
        *@param pOwner - component owner
        */
        TSP_Component(const std::wstring& title,
                      const std::wstring& description,
                      const std::wstring& comments,
                            TSP_Page*     pOwner);

        virtual ~TSP_Component();

        /**
        * Gets the title
        *@return the title
        */
        virtual std::wstring GetTitle() const;

        /**
        * Sets the title
        *@param value - the title
        *@return true on success, otherwise false
        */
        virtual bool SetTitle(const std::wstring& value);

        /**
        * Gets the description
        *@return the description
        */
        virtual std::wstring GetDescription() const;

        /**
        * Sets the description
        *@param value - the description
        *@return true on success, otherwise false
        */
        virtual bool SetDescription(const std::wstring& value);

        /**
        * Gets the comments
        *@return the comments
        */
        virtual std::wstring GetComments() const;

        /**
        * Sets the comments
        *@param value - the comments
        *@return true on success, otherwise false
        */
        virtual bool SetComments(const std::wstring& value);

    protected:
        TSP_Item* m_pOwner = nullptr;

    private:
        TSP_Attributes m_Attributes;
        std::wstring   m_Title; // FIXME attribute?
        std::wstring   m_Description; // FIXME attribute?
        std::wstring   m_Comments; // FIXME attribute?

        // FIXME
        /*
        typedef std::vector<TSP_Component*> IComponents;
        IComponents m_Entering;
        TSP_Components m_Exiting;
        TSP_Components m_EnteringSide;
        TSP_Components m_ExitingSide;
        */
};
