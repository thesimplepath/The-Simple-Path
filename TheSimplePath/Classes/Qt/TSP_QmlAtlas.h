/****************************************************************************
 * ==> TSP_QmlAtlas --------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document atlas                                          *
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
#include "Core\TSP_Atlas.h"

// qt classes
#include "TSP_QmlDocument.h"
#include "TSP_QmlAtlasProxy.h"

/**
* Qt document atlas
*@author Jean-Milost Reymond
*/
class TSP_QmlAtlas : public TSP_Atlas
{
    public:
        /**
        * Constructor
        *@param pOwner - the atlas owner
        */
        TSP_QmlAtlas(TSP_QmlDocument* pOwner);

        /**
        * Constructor
        *@param name - the atlas name
        *@param pOwner - the atlas owner
        */
        TSP_QmlAtlas(const std::wstring& name, TSP_QmlDocument* pOwner);

        virtual ~TSP_QmlAtlas();

        /**
        * Gets the atlas proxy
        *@return the atlas proxy, nullptr if no proxy
        */
        TSP_QmlAtlasProxy* GetProxy() const;

        /**
        * Sets the atlas proxy
        *@param pProxy - the atlas proxy
        */
        void SetProxy(TSP_QmlAtlasProxy* pProxy);

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
        * Adds a new page in atlas
        *@return newly added page
        */
        virtual TSP_Page* AddPage();

        /**
        * Adds a new page in atlas
        *@param name - page name
        *@return newly added page
        */
        virtual TSP_Page* AddPage(const std::wstring& name);

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

        /**
        * Gets the currently selected page
        *@return the currently selected page, nullptr if no page selected or on error
        */
        virtual TSP_Page* GetSelectedPage() const;

    private:
        TSP_QmlAtlasProxy* m_pProxy = nullptr;
};
