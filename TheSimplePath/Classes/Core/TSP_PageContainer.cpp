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

#include "TSP_PageContainer.h"

// std
#include <memory>

// core classes
#include "TSP_Document.h"

//---------------------------------------------------------------------------
// TSP_PageContainer
//---------------------------------------------------------------------------
TSP_PageContainer::TSP_PageContainer()
{}
//---------------------------------------------------------------------------
TSP_PageContainer::~TSP_PageContainer()
{
    for each (auto pPage in m_Pages)
        delete pPage;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageContainer::CreateAndAddPage()
{
    std::unique_ptr<TSP_Page> pPage(CreatePage());
    m_Pages.push_back(pPage.get());
    return pPage.release();
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageContainer::CreateAndAddPage(const std::wstring& name)
{
    std::unique_ptr<TSP_Page> pPage(CreatePage(name));
    m_Pages.push_back(pPage.get());
    return pPage.release();
}
//---------------------------------------------------------------------------
void TSP_PageContainer::RemovePage(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Pages.size())
        return;

    // delete the page
    delete m_Pages[index];
    m_Pages.erase(m_Pages.begin() + index);
}
//---------------------------------------------------------------------------
void TSP_PageContainer::RemovePage(TSP_Page* pPage)
{
    // search for page to remove
    for (std::size_t i = 0; i < m_Pages.size(); ++i)
        // found it?
        if (m_Pages[i] == pPage)
        {
            // remove the page and exit
            RemovePage(i);
            return;
        }
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageContainer::GetPage(std::size_t index) const
{
    if (index >= m_Pages.size())
        return nullptr;

    return m_Pages[index];
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageContainer::GetPage(const std::string& uid) const
{
    for each (auto pPage in m_Pages)
        if (pPage->GetUID() == uid)
            return pPage;

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t TSP_PageContainer::GetPageCount() const
{
    return m_Pages.size();
}
//---------------------------------------------------------------------------
bool TSP_PageContainer::Load()
{
    //m_NbrGen;
    //m_Name

    /*
    for each (auto pModel in m_Models)
        pModel->Load();
    */

    return true;
}
//---------------------------------------------------------------------------
bool TSP_PageContainer::Save() const
{
    //m_NbrGen;
    //m_Name

    /*
    for each (auto pModel in m_Models)
        pModel->Save();
    */

    return true;
}
//---------------------------------------------------------------------------
