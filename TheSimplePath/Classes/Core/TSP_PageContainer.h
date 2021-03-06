/****************************************************************************
 * ==> TSP_PageContainer ---------------------------------------------------*
 ****************************************************************************
 * Description:  Container which may contain pages                          *
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
#include <string>
#include <vector>

// core class
#include "TSP_Page.h"

/**
* Container which may contain pages
*@author Jean-Milost Reymond
*/
class TSP_PageContainer
{
    public:
        TSP_PageContainer();
        virtual ~TSP_PageContainer();

        /**
        * Creates a page
        *@return newly created page
        */
        virtual TSP_Page* CreatePage() = 0;

        /**
        * Creates a page
        *@param name - page name
        *@return newly created page
        */
        virtual TSP_Page* CreatePage(const std::wstring& name) = 0;

        /**
        * Creates a new page and adds it in container
        *@return newly added page
        */
        virtual TSP_Page* CreateAndAddPage();

        /**
        * Creates a new page and adds it in container
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

        /**
        * Gets page at index
        *@param index - page index to get
        *@return page, nullptr if not found or on error
        */
        virtual TSP_Page* GetPage(std::size_t index) const;

        /**
        * Gets page matching with unique identifier
        *@param uid - page unique identifier to get
        *@return page, nullptr if not found or on error
        */
        virtual TSP_Page* GetPage(const std::string& uid) const;

        /**
        * Gets page count
        *@return page count
        */
        virtual std::size_t GetPageCount() const;

        /**
        * Loads a model from a file
        *@return true on success, otherwise false
        */
        virtual bool Load();

        /**
        * Saves a model to a file
        *@return true on success, otherwise false
        */
        virtual bool Save() const;

    protected:
        typedef std::vector<TSP_Page*> IPages;

        IPages      m_Pages;
        std::size_t m_NewPageNbGen =  0;
};
