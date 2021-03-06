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

#include "TSP_QmlAtlas.h"

// std
#include <sstream>

 // common classes
#include "Common/TSP_Exception.h"
#include "Common/TSP_GlobalMacros.h"

// qt classes
#include "TSP_QmlPage.h"
#include "TSP_QmlProxyDictionary.h"

//---------------------------------------------------------------------------
// TSP_QmlAtlas
//---------------------------------------------------------------------------
TSP_QmlAtlas::TSP_QmlAtlas(TSP_QmlDocument* pOwner) :
    TSP_Atlas(pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlas::TSP_QmlAtlas(const std::wstring& name, TSP_QmlDocument* pOwner) :
    TSP_Atlas(name, pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlas::~TSP_QmlAtlas()
{}
//---------------------------------------------------------------------------
TSP_QmlAtlasProxy* TSP_QmlAtlas::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::SetProxy(TSP_QmlAtlasProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreatePage()
{
    return new TSP_QmlPage(this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreatePage(const std::wstring& name)
{
    return new TSP_QmlPage(name, this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreateAndAddPage()
{
    M_TRY
    {
        std::wostringstream sstr;

        //: New page default name
        //% "New page"
        sstr << qtTrId("id-new-page").toStdWString();

        if (m_NewPageNbGen)
            sstr << L" (" << std::to_wstring(m_NewPageNbGen) << L")";

        ++m_NewPageNbGen;

        return CreateAndAddPage(sstr.str());
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreateAndAddPage(const std::wstring& name)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Create and add page - FAILED - atlas proxy is missing");
            return nullptr;
        }

        // add a new page in atlas
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(TSP_PageContainer::CreateAndAddPage(name));

        // succeeded?
        if (!pQmlPage)
        {
            M_LogErrorT("Create and add page - FAILED - page could not be created");
            return nullptr;
        }

        // create a new page view and adds it on the user interface
        if (!CreatePageView(pQmlPage))
        {
            M_LogErrorT("Create and add page - FAILED - page view could not be created");
            TSP_PageContainer::RemovePage(pQmlPage);
            return nullptr;
        }

        return pQmlPage;
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::RemovePage(std::size_t index)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Remove page - FAILED - atlas proxy is missing");
            return;
        }

        // get the page to remove
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(GetPage(index));

        // found it?
        if (!pQmlPage)
            return;

        // notify atlas proxy that a page was removed
        m_pProxy->RemovePage(QString::fromStdString(pQmlPage->GetUID()));

        // remove the page from document
        TSP_PageContainer::RemovePage(index);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::RemovePage(TSP_Page* pPage)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Remove page - FAILED - atlas proxy is missing");
            return;
        }

        // get the page to remove
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(pPage);

        // found it?
        if (!pQmlPage)
            return;

        // notify atlas proxy that a page was removed
        m_pProxy->RemovePage(QString::fromStdString(pQmlPage->GetUID()));

        // remove the page from document
        TSP_PageContainer::RemovePage(pPage);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::GetSelectedPage()
{
    M_TRY
    {
        if (!m_pProxy)
            return nullptr;

        // get currently selected owner unique identifier
        const std::string selectedOwnerUID = m_pProxy->QuerySelectedPageOwnerUID().toStdString();

        // is this atlas the currently selected one on the user interface?
        if (selectedOwnerUID.empty() || selectedOwnerUID != GetUID())
            // the selected page cannot be currently shown on the interface
            return nullptr;

        // queries the selected page unique identifier
        m_SelectedPageUID = m_pProxy->QuerySelectedPageUID().toStdString();

        // found it?
        if (m_SelectedPageUID.empty())
            return nullptr;

        // get the selected page
        return GetPage(m_SelectedPageUID);
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
bool TSP_QmlAtlas::CreatePageView(TSP_Page* pPage)
{
    if (!pPage)
        return false;

    if (!m_pProxy)
        return false;

    // get page unique identifier
    const std::string uid = pPage->GetUID();

    // notify atlas proxy that a new page should be added
    if (!m_pProxy->AddPage(QString::fromStdString(uid)))
        return false;

    // get the page
    TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(pPage);

    if (!pQmlPage)
        return false;

    // get the newly added component proxy
    TSP_QmlPageProxy* pProxy = static_cast<TSP_QmlPageProxy*>(TSP_QmlProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the page and its proxy
    pQmlPage->SetProxy(pProxy);
    pProxy->SetPage(pQmlPage);

    return true;
}
//---------------------------------------------------------------------------
