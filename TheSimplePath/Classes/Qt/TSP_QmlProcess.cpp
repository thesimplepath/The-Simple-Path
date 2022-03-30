/****************************************************************************
 * ==> TSP_QmlProcess ------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt process component                                       *
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

#include "TSP_QmlProcess.h"

// std
#include <sstream>

// common classes
#include "Common/TSP_Exception.h"
#include "Common/TSP_GlobalMacros.h"

// qt classes
#include "TSP_QmlPage.h"

//---------------------------------------------------------------------------
// TSP_QmlProcess
//---------------------------------------------------------------------------
TSP_QmlProcess::TSP_QmlProcess(TSP_QmlPage* pOwner) :
    TSP_Process(pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlProcess::TSP_QmlProcess(const std::wstring& title,
                               const std::wstring& description,
                               const std::wstring& comments,
                                     TSP_QmlPage*  pOwner) :
    TSP_Process(title, description, comments, pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlProcess::~TSP_QmlProcess()
{}
//---------------------------------------------------------------------------
TSP_QmlBoxProxy* TSP_QmlProcess::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void TSP_QmlProcess::SetProxy(TSP_QmlBoxProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlProcess::CreatePage()
{
    return new TSP_QmlPage(this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlProcess::CreatePage(const std::wstring& name)
{
    return new TSP_QmlPage(name, this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlProcess::CreateAndAddPage()
{
    M_TRY
    {
        std::wostringstream sstr;

        //: New process page default name
        //% "New process page"
        sstr << qtTrId("id-new-process-page").toStdWString();

        if (m_NewPageNbGen)
            sstr << L" (" << std::to_wstring(m_NewPageNbGen) << L")";

        ++m_NewPageNbGen;

        return CreateAndAddPage(sstr.str());
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlProcess::CreateAndAddPage(const std::wstring& name)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Create and add page - FAILED - box proxy is missing");
            return nullptr;
        }

        // add a new page in this process
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
void TSP_QmlProcess::RemovePage(std::size_t index)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Remove page - FAILED - box proxy is missing");
            return;
        }

        // get the page to remove
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(GetPage(index));

        // found it?
        if (!pQmlPage)
            return;

        // notify box proxy that a page was removed
        m_pProxy->RemoveItem("page", QString::fromStdString(pQmlPage->GetUID()));

        // remove the page from document
        TSP_PageContainer::RemovePage(index);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
void TSP_QmlProcess::RemovePage(TSP_Page* pPage)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Remove page - FAILED - page proxy is missing");
            return;
        }

        // get the page to remove
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(pPage);

        // found it?
        if (!pQmlPage)
            return;

        // notify box proxy that a page was removed
        m_pProxy->RemoveItem("page", QString::fromStdString(pQmlPage->GetUID()));

        // remove the page from document
        TSP_PageContainer::RemovePage(pPage);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
bool TSP_QmlProcess::CreatePageView(TSP_Page* pPage)
{
    if (!m_pProxy)
        return false;

    // get the qml page
    TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(pPage);

    if (!pQmlPage)
        return false;

    // get page unique identifier
    const std::string uid = pPage->GetUID();

    // notify box proxy that a new page should be added
    if (!m_pProxy->AddItem("page", QString::fromStdString(uid)))
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
