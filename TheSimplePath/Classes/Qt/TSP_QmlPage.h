/****************************************************************************
 * ==> TSP_QmlPage ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document page                                           *
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
#include <vector>

// core classes
#include "Core\TSP_Page.h"

// qt classes
#include "TSP_QmlAtlas.h"
#include "TSP_QmlPageProxy.h"
#include "TSP_QmlDocPageProxy.h"

/**
* Qt document page
*@author Jean-Milost Reymond
*/
class TSP_QmlPage : public TSP_Page
{
    public:
        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_QmlPage(TSP_QmlAtlas* pOwner);

        /**
        * Constructor
        *@param name - the page name
        *@param pOwner - the page owner
        */
        TSP_QmlPage(const std::wstring& name, TSP_QmlAtlas* pOwner);

        virtual ~TSP_QmlPage();

        /**
        * Gets the page proxy
        *@return the page proxy, nullptr if no proxy
        */
        TSP_QmlPageProxy* GetProxy() const;

        /**
        * Sets the page proxy
        *@param pProxy - the page proxy
        */
        void SetProxy(TSP_QmlPageProxy* pProxy);

        /**
        * Gets the document page proxy
        *@return the document page proxy, nullptr if no proxy
        */
        TSP_QmlDocPageProxy* GetDocProxy() const;

        /**
        * Sets the document page proxy
        *@param pProxy - the document page proxy
        */
        void SetDocProxy(TSP_QmlDocPageProxy* pProxy);

        /**
        * Checks if the page is a child of another page
        *@return true if the page is a child of another page, otherwise false
        */
        virtual inline bool IsChild() const;

    private:
        TSP_QmlPageProxy*    m_pProxy    = nullptr;
        TSP_QmlDocPageProxy* m_pDocProxy = nullptr;
};

//---------------------------------------------------------------------------
// TSP_QmlPage
//---------------------------------------------------------------------------
bool TSP_QmlPage::IsChild() const
{
    return dynamic_cast<TSP_QmlPage*>(m_pOwner);
}
//---------------------------------------------------------------------------
