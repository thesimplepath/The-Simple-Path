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
#include "Qt/TSP_QmlAtlasPage.h"
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
        // no application?
        if (!m_pApp)
        {
            M_LogErrorT("onNewDocumentClicked - FAILED - no application defined");
            return;
        }

        // no document?
        if (!m_pApp->GetDocument())
        {
            M_LogErrorT("onNewDocumentClicked - FAILED - no document defined");
            return;
        }

        // create the document
        if (!m_pApp->GetDocument()->Create())
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
        // no application?
        if (!m_pApp)
        {
            M_LogErrorT("onNewDocumentClicked - FAILED - no application defined");
            return;
        }

        // no document?
        if (!m_pApp->GetDocument())
        {
            M_LogErrorT("onNewDocumentClicked - FAILED - no document defined");
            return;
        }

        // close the document
        m_pApp->GetDocument()->Close();
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onAddProcessClicked()
{
    M_TRY
    {
        // FIXME create a generic function in document to get selected atlas and page
        // no application?
        if (!m_pApp)
        {
            M_LogErrorT("onAddProcessClicked - FAILED - no application defined");
            return;
        }

        // get document
        TSP_QmlDocument* pDoc = m_pApp->GetDocument();

        // no document?
        if (!pDoc)
        {
            M_LogErrorT("onAddProcessClicked - FAILED - no document defined");
            return;
        }

        // get selected atlas
        TSP_QmlAtlas* pSelectedAtlas = static_cast<TSP_QmlAtlas*>(pDoc->GetSelectedAtlas());

        // no selected atlas?
        if (!pSelectedAtlas)
        {
            M_LogWarnT("onAddProcessClicked - no selected atlas");
            return;
        }

        // get selected page
        TSP_QmlAtlasPage* pSelectedPage = static_cast<TSP_QmlAtlasPage*>(pSelectedAtlas->GetSelectedPage());

        // no selected page?
        if (!pSelectedPage)
        {
            M_LogWarnT("onAddProcessClicked - no selected page");
            return;
        }

        //: New process title
        //% "New process"
        const QString defProcessTitle = qtTrId("id-new-process-title");

        // FIXME use add process instead (when created)
        // add process
        if (!pSelectedPage->CreateAndAddBox(defProcessTitle.toStdWString()))
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
