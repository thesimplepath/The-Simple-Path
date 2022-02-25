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

#include "TSP_Page.h"

// core classes
#include "TSP_Atlas.h"

//---------------------------------------------------------------------------
// TSP_Page
//---------------------------------------------------------------------------
TSP_Page::TSP_Page(TSP_Item* pOwner) :
    TSP_Item(),
    m_pOwner(pOwner)
{}
//---------------------------------------------------------------------------
TSP_Page::TSP_Page(const std::wstring& name, TSP_Item* pOwner) :
    TSP_Item(),
    m_Name(name),
    m_pOwner(pOwner)
{}
//---------------------------------------------------------------------------
TSP_Page::~TSP_Page()
{
    for each (auto pComponent in m_Components)
        delete pComponent;
}
//---------------------------------------------------------------------------
TSP_Box* TSP_Page::CreateAndAddBox(const std::wstring& name,
                                   const std::wstring& description,
                                   const std::wstring& comments)
{
    std::unique_ptr<TSP_Box> pBox = std::make_unique<TSP_Box>(name, description, comments, this);
    m_Components.push_back(pBox.get());
    return pBox.release();
}
//---------------------------------------------------------------------------
TSP_Link* TSP_Page::CreateAndAddLink(const std::wstring& name,
                                     const std::wstring& description,
                                     const std::wstring& comments)
{
    std::unique_ptr<TSP_Link> pLink = std::make_unique<TSP_Link>(name, description, comments, this);
    m_Components.push_back(pLink.get());
    return pLink.release();
}
//---------------------------------------------------------------------------
void TSP_Page::Remove(const std::string& uid)
{
    TSP_Page::Remove(Get(uid));
}
//---------------------------------------------------------------------------
void TSP_Page::Remove(TSP_Component* pComponent)
{
    if (!pComponent)
        return;

    for (std::size_t i = 0; i < m_Components.size(); ++i)
        if (m_Components[i] == pComponent)
        {
            delete m_Components[i];
            m_Components.erase(m_Components.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
TSP_Component* TSP_Page::Get(const std::string& uid) const
{
    for each (auto pComponent in m_Components)
        if (pComponent->GetUID() == uid)
            return pComponent;

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t TSP_Page::GetCount() const
{
    return m_Components.size();
}
//---------------------------------------------------------------------------
bool TSP_Page::Add(TSP_Component* pComponent)
{
    // no component?
    if (!pComponent)
        return false;

    // check if component was already added in component list
    for each (auto pComp in m_Components)
        if (pComponent == pComp)
            return false;

    // add the component to component list
    m_Components.push_back(pComponent);

    return true;
}
//---------------------------------------------------------------------------
