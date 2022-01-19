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
TSP_Page::TSP_Page(TSP_Atlas* pOwner) :
    TSP_Item(),
    m_pOwner(pOwner)
{}
//---------------------------------------------------------------------------
TSP_Page::TSP_Page(const std::wstring& name, TSP_Atlas* pOwner) :
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
TSP_Activity* TSP_Page::AddActivity()
{
    // FIXME config parameters
    return AddActivity(L"", L"", L"", 0, 0);
}
//---------------------------------------------------------------------------
TSP_Activity* TSP_Page::AddActivity(const std::wstring& name,
                                    const std::wstring& description,
                                    const std::wstring& comments,
                                          int           x,
                                          int           y)
{
    // FIXME handle x and y params
    std::unique_ptr<TSP_Activity> pActivity =
            std::make_unique<TSP_Activity>(name, description, comments, this);
    m_Components.push_back(pActivity.get());
    return pActivity.release();
}
//---------------------------------------------------------------------------
void TSP_Page::RemoveActivity(const std::string& uid)
{
    RemoveActivity(GetActivity(uid));
}
//---------------------------------------------------------------------------
void TSP_Page::RemoveActivity(TSP_Activity* pActivity)
{
    if (!pActivity)
        return;

    for (std::size_t i = 0; i < m_Components.size(); ++i)
        if (m_Components[i] == pActivity)
        {
            delete m_Components[i];
            m_Components.erase(m_Components.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
TSP_Activity* TSP_Page::GetActivity(const std::string& uid) const
{
    for each (auto pComponent in m_Components)
        if (pComponent->GetUID() == uid)
        {
            TSP_Activity* pActivity = dynamic_cast<TSP_Activity*>(pComponent);

            if (pActivity)
                return pActivity;
        }

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t TSP_Page::GetActivityCount() const
{
    std::size_t count = 0;

    for each (auto pComponent in m_Components)
    {
        TSP_Activity* pActivity = dynamic_cast<TSP_Activity*>(pComponent);

        if (pActivity)
            return ++count;
    }

    return count;
}
//---------------------------------------------------------------------------
std::size_t TSP_Page::GetComponentCount() const
{
    return m_Components.size();
}
//---------------------------------------------------------------------------
