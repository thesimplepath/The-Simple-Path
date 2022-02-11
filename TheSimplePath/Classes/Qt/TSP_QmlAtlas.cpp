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
TSP_Page* TSP_QmlAtlas::AddPage()
{
    M_TRY
    {
        std::wostringstream sstr;

        //: New page default name
        //% "New page"
        sstr << qtTrId("id-new-page").toStdWString();

        const std::size_t pageCount = GetPageCount();

        // FIXME this doesn't work, what happens if a random page is removed?
        if (pageCount)
            sstr << L" (" << std::to_wstring(pageCount) << L")";

        return AddPage(sstr.str());
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::AddPage(const std::wstring& name)
{
    M_TRY
    {
        if (!m_pProxy)
        {
            M_LogErrorT("Add page - FAILED - atlas proxy is missing");
            return nullptr;
        }

        // add a new page in atlas
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(TSP_Atlas::AddPage(name));

        // succeeded?
        if (!pQmlPage)
        {
            M_LogErrorT("Add page - FAILED - page could not be created");
            return nullptr;
        }

        // notify atlas proxy that a new page should be added
        if (!m_pProxy->AddPage(QString::fromStdString(pQmlPage->GetUID())))
        {
            M_LogErrorT("Add page - FAILED - page could not be added on view");
            TSP_Atlas::RemovePage(pQmlPage);
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
        TSP_Atlas::RemovePage(index);
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
        TSP_Atlas::RemovePage(pPage);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::GetSelectedPage() const
{
    return nullptr;
}
//---------------------------------------------------------------------------
