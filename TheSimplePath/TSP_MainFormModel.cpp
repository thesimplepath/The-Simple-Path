/****************************************************************************
 * ==> TSP_MainFormModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  Main form model                                            *
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

#include "TSP_MainFormModel.h"

// common classes
#include "Common/TSP_GlobalMacros.h"

// qt classes
#include "Qt/TSP_QmlDocument.h"
#include "Qt/TSP_QmlAtlas.h"
#include "Qt/TSP_QmlPage.h"
#include "Qt/TSP_QtGlobalMacros.h"

// application
#include "TSP_Application.h"

// qt
#include <QSize>

// windows
#include <windows.h>

//---------------------------------------------------------------------------
// TSP_MainFormModel
//---------------------------------------------------------------------------
TSP_MainFormModel::TSP_MainFormModel(TSP_Application* pApp, QObject* pParent) :
    QObject(pParent),
    m_pApp(pApp)
{}
//---------------------------------------------------------------------------
TSP_MainFormModel::~TSP_MainFormModel()
{}
//---------------------------------------------------------------------------
int TSP_MainFormModel::getPageWidth() const
{
    int width = 0;
    HDC hDC   = ::GetDC(nullptr);

    try
    {
        const float ppx   = ::GetDeviceCaps(hDC, LOGPIXELSX);
                    width = std::ceilf(m_PageSize.size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point).width() * (ppx / 72.0f));
    }
    catch (...)
    {}

    if (hDC)
        ::ReleaseDC(nullptr, hDC);

    return width;
}
//---------------------------------------------------------------------------
int TSP_MainFormModel::getPageHeight() const
{
    int height = 0;
    HDC hDC    = ::GetDC(nullptr);

    try
    {
        const float ppx    = ::GetDeviceCaps(hDC, LOGPIXELSY);
                    height = std::ceilf(m_PageSize.size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point).height() * (ppx / 72.0f));
    }
    catch (...)
    {}

    if (hDC)
        ::ReleaseDC(nullptr, hDC);

    return height;
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::showError(const QString& title, const QString& msg, const QString& detailedMsg)
{
    emit showErrorDialog(title, msg, detailedMsg);
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onNewDocumentClicked()
{
    M_TRY
    {
        // get document
        TSP_QmlDocument* pDoc = GetDocument();

        // no document?
        if (!pDoc)
        {
            M_LogErrorT("onNewDocumentClicked - FAILED - no document defined");
            return;
        }

        // create the document
        if (!pDoc->Create())
        {
            //: Create document error dialog title
            //% "Create new document"
            const QString title = qtTrId("id-error-create-doc-title");

            //: Create document error dialog message
            //% "Failed to create the new document."
            const QString msg = qtTrId("id-error-create-doc-msg");

            showError(title, msg);
        }
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onCloseDocumentClicked()
{
    M_TRY
    {
        // get document
        TSP_QmlDocument* pDoc = GetDocument();

        // no document?
        if (!pDoc)
        {
            M_LogErrorT("onCloseDocumentClicked - FAILED - no document defined");
            return;
        }

        // close the document
        pDoc->Close();
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onAddBoxClicked()
{
    M_TRY
    {
        // get selected page
        TSP_QmlPage* pSelectedPage = static_cast<TSP_QmlPage*>(GetSelectedPage());

        // no selected page?
        if (!pSelectedPage)
        {
            M_LogWarnT("onAddBoxClicked - no selected page");
            return;
        }

        //: New box title
        //% "New box"
        const QString defProcessTitle = qtTrId("id-new-box-title");

        // add box
        if (!pSelectedPage->CreateAndAddBox(defProcessTitle.toStdWString()))
        {
            //: Create box error dialog title
            //% "Create new box"
            const QString title = qtTrId("id-error-create-box-title");

            //: Create box error dialog message
            //% "Failed to create the new box."
            const QString msg = qtTrId("id-error-create-box-msg");

            showError(title, msg);
        }
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onAddProcessClicked()
{
    M_TRY
    {
        // FIXME for Jean: Find a better way to determine if page is an atlas page or a process page
        // get selected page
        TSP_QmlPage* pSelectedPage = dynamic_cast<TSP_QmlPage*>(GetSelectedPage());

        // no selected page?
        if (!pSelectedPage)
        {
            M_LogWarnT("onAddProcessClicked - no selected page");
            return;
        }

        //: New process title
        //% "New process"
        const QString defProcessTitle = qtTrId("id-new-process-title");

        // add process
        if (!pSelectedPage->CreateAndAddProcess(defProcessTitle.toStdWString()))
        {
            //: Create process error dialog title
            //% "Create new process"
            const QString title = qtTrId("id-error-create-process-title");

            //: Create process error dialog message
            //% "Failed to create the new process."
            const QString msg = qtTrId("id-error-create-process-msg");

            showError(title, msg);
        }
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
TSP_QmlDocument* TSP_MainFormModel::GetDocument() const
{
    // no application?
    if (!m_pApp)
        return nullptr;

    // get document
    return m_pApp->GetDocument();
}
//---------------------------------------------------------------------------
TSP_QmlAtlas* TSP_MainFormModel::GetSelectedAtlas() const
{
    // get document
    TSP_QmlDocument* pDoc = GetDocument();

    // no document?
    if (!pDoc)
        return nullptr;

    // get selected atlas
    return static_cast<TSP_QmlAtlas*>(pDoc->GetSelectedAtlas());
}
//---------------------------------------------------------------------------
TSP_QmlPage* TSP_MainFormModel::GetSelectedPage() const
{
    // get selected atlas
    TSP_QmlAtlas* pSelectedAtlas = GetSelectedAtlas();

    // no selected atlas?
    if (!pSelectedAtlas)
        return nullptr;

    // FIXME for Jean: Need a way to retrieve the REAL selected page, may be an atlas page, or a process page
    // get selected page
    return static_cast<TSP_QmlPage*>(pSelectedAtlas->GetSelectedPage());
}
//---------------------------------------------------------------------------
