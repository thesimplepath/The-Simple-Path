/****************************************************************************
 * ==> TSP_Page ------------------------------------------------------------*
 ****************************************************************************
 * Description:  Document page                                              *
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
#include "TSP_Box.h"
#include "TSP_Link.h"

/**
* Document page
*@author Jean-Milost Reymond
*/
class TSP_Page : public TSP_Item
{
    public:
        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_Page(TSP_Item* pOwner);

        /**
        * Constructor
        *@param name - the page name
        *@param pOwner - the page owner
        */
        TSP_Page(const std::wstring& name, TSP_Item* pOwner);

        virtual ~TSP_Page();

        /**
        * Gets the page owner
        *@return the page owner
        */
        virtual inline TSP_Item* GetOwner() const;

        /**
        * Gets the model name
        *@return the model name
        */
        virtual inline std::wstring GetName() const;

        /**
        * Sets the model name
        *@param name - the model name
        */
        virtual inline void SetName(const std::wstring& name);

        /**
        * Creates a box and adds it in page
        *@param name - box name
        *@param description - box description
        *@param comments - box comments
        *@return newly created box
        */
        virtual TSP_Box* CreateAndAddBox(const std::wstring& name,
                                         const std::wstring& description,
                                         const std::wstring& comments);

        /**
        * Creates a link and adds it in page
        *@param name - link name
        *@param description - link description
        *@param comments - link comments
        *@return newly created link
        */
        virtual TSP_Link* CreateAndAddLink(const std::wstring& name,
                                           const std::wstring& description,
                                           const std::wstring& comments);

        /**
        * Removes a component
        *@param uid - component unique identifier to remove
        */
        virtual void Remove(const std::string& uid);

        /**
        * Removes a component
        *@param pComponent - component to remove
        */
        virtual void Remove(TSP_Component* pComponent);

        /**
        * Gets a component
        *@param uid - component unique identifier to get
        *@return component, nullptr if not found or on error
        */
        virtual TSP_Component* Get(const std::string& uid) const;

        /**
        * Gets count of type
        *@return count of type
        */
        template <class T>
        std::size_t GetCountOf() const;

        /**
        * Gets component count
        *@return component count
        */
        virtual std::size_t GetCount() const;

    protected:
        /**
        * Adds a component in page
        *@param pComponent - component to add
        *@return true on success, otherwise false
        *@note The component lifetime will be managed internally, don't try to delete it from outside
        */
        virtual bool Add(TSP_Component* pComponent);

    private:
        typedef std::vector<TSP_Component*> IComponents;

        TSP_Item*    m_pOwner = nullptr;
        IComponents  m_Components;
        std::wstring m_Name;
};

//---------------------------------------------------------------------------
// TSP_Page
//---------------------------------------------------------------------------
TSP_Item* TSP_Page::GetOwner() const
{
    return m_pOwner;
}
//---------------------------------------------------------------------------
std::wstring TSP_Page::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void TSP_Page::SetName(const std::wstring& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
template <class T>
std::size_t TSP_Page::GetCountOf() const
{
    std::size_t count = 0;

    for each (auto pComponent in m_Components)
        if (dynamic_cast<T*>(pComponent))
            ++count;

    return count;
}
//---------------------------------------------------------------------------
