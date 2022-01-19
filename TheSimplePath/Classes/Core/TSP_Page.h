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
#include "TSP_Activity.h"

// class prototypes
class TSP_Atlas;

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
        TSP_Page(TSP_Atlas* pOwner);

        /**
        * Constructor
        *@param name - the page name
        *@param pOwner - the page owner
        */
        TSP_Page(const std::wstring& name, TSP_Atlas* pOwner);

        virtual ~TSP_Page();

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
        * Adds a new activity in page
        *@return newly added activity
        */
        virtual TSP_Activity* AddActivity();

        /**
        * Adds a new activity in page
        *@param name - activity name
        *@param description - activity description
        *@param comments - activity comments
        *@param x - activity x position on page, in pixels
        *@param y - activity y position on page, in pixels
        *@return newly added activity
        */
        virtual TSP_Activity* AddActivity(const std::wstring& name,
                                          const std::wstring& description,
                                          const std::wstring& comments,
                                                int           x,
                                                int           y);

        /**
        * Removes an activity
        *@param uid - activity unique identifier to remove
        */
        virtual void RemoveActivity(const std::string& uid);

        /**
        * Removes an activity
        *@param pActivity - activity to remove
        */
        virtual void RemoveActivity(TSP_Activity* pActivity);

        /**
        * Gets an activity
        *@param uid - activity unique identifier to get
        *@return activity, nullptr if not found or on error
        */
        virtual TSP_Activity* GetActivity(const std::string& uid) const;

        /**
        * Gets activity count
        *@return activity count
        */
        virtual std::size_t GetActivityCount() const;

        /**
        * Gets component count
        *@return component count
        */
        virtual std::size_t GetComponentCount() const;

    private:
        typedef std::vector<TSP_Component*> IComponents;

        TSP_Atlas*   m_pOwner;
        IComponents  m_Components;
        std::wstring m_Name;
};

//---------------------------------------------------------------------------
// TSP_Page
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
