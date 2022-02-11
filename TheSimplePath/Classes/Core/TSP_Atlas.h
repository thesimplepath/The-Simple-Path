/****************************************************************************
 * ==> TSP_Atlas -----------------------------------------------------------*
 ****************************************************************************
 * Description:  Document atlas                                             *
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
#include "TSP_Item.h"
#include "TSP_Page.h"

// class prototypes
class TSP_Document;

/**
* Document atlas
*@author Jean-Milost Reymond
*/
class TSP_Atlas : public TSP_Item
{
    public:
        /**
        * Constructor
        *@param pOwner - the atlas owner
        */
        TSP_Atlas(TSP_Document* pOwner);

        /**
        * Constructor
        *@param name - the atlas name
        *@param pOwner - the atlas owner
        */
        TSP_Atlas(const std::wstring& name, TSP_Document* pOwner);

        virtual ~TSP_Atlas();

        /**
        * Gets the atlas name
        *@return the atlas name
        */
        virtual inline std::wstring GetName() const;

        /**
        * Sets the atlas name
        *@param name - the atlas name
        */
        virtual inline void SetName(const std::wstring& name);

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
        * Gets page at index
        *@param index - page index to get
        *@return page, nullptr if not found or on error
        */
        virtual TSP_Page* GetPage(std::size_t index) const;

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
        TSP_Document* m_pOwner = nullptr;

    private:
        typedef std::vector<TSP_Page*> IPages;

        IPages       m_Pages;
        std::wstring m_Name;
};

//---------------------------------------------------------------------------
// TSP_Atlas
//---------------------------------------------------------------------------
std::wstring TSP_Atlas::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void TSP_Atlas::SetName(const std::wstring& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
