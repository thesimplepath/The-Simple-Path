/****************************************************************************
 * ==> TSP_QmlProcess ------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt process component                                       *
 * Contained in: Qt                                                         *
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
#include <map>

// core classes
#include "Core\TSP_Process.h"

// qt classes
#include "TSP_QmlBoxProxy.h"

// classes prototypes
class TSP_QmlPage;

/**
* Qt process component
*@author Jean-Milost Reymond
*/
class TSP_QmlProcess : public TSP_Process
{
    public:
        /**
        * Constructor
        *@param pOwner - page owner
        */
        TSP_QmlProcess(TSP_QmlPage* pOwner);

        /**
        * Constructor
        *@param title - component title
        *@param description - component description
        *@param comments - component comments
        *@param pOwner - page owner
        */
        TSP_QmlProcess(const std::wstring& title,
                       const std::wstring& description,
                       const std::wstring& comments,
                             TSP_QmlPage*  pOwner);

        virtual ~TSP_QmlProcess();

        /**
        * Gets the box proxy
        *@return the box proxy, nullptr if no proxy
        */
        TSP_QmlBoxProxy* GetProxy() const;

        /**
        * Sets the box proxy
        *@param pProxy - the box proxy
        */
        void SetProxy(TSP_QmlBoxProxy* pProxy);

        /**
        * Creates a page
        *@return newly created page
        */
        virtual TSP_Page* CreatePage();

        /**
        * Creates a page
        *@param name - page name
        *@return newly created page
        */
        virtual TSP_Page* CreatePage(const std::wstring& name);

        /**
        * Creates a new child page and adds it in this page
        *@return newly added page
        */
        virtual TSP_Page* CreateAndAddPage();

        /**
        * Creates a new child page and adds it in this page
        *@param name - page name
        *@return newly added page
        */
        virtual TSP_Page* CreateAndAddPage(const std::wstring& name);

        /**
        * Removes a page
        *@param index - page index to remove
        */
        virtual void RemovePage(std::size_t index);

        /**
        * Removes a page
        *@param pPage - page to remove
        */
        virtual void RemovePage(TSP_Page* pPage);

    private:
        TSP_QmlBoxProxy* m_pProxy = nullptr;

        /**
        * Creates a new page view and adds it to the user interface
        *@param pPage - page for which the view should be added
        */
        bool CreatePageView(TSP_Page* pPage);
};
