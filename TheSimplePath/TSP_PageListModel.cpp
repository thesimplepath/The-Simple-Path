/****************************************************************************
 * ==> TSP_PageListModel ---------------------------------------------------*
 ****************************************************************************
 * Description: Page list model                                             *
 * Developer:   Jean-Milost Reymond                                         *
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

#include "TSP_PageListModel.h"

 // application
#include "TSP_Application.h"

// common classes
#include "Common/TSP_Exception.h"
#include "Common/TSP_GlobalMacros.h"

// qt classes
#include "Qt/TSP_QmlDocument.h"
#include "Qt/TSP_QmlAtlas.h"
#include "Qt/TSP_QmlPage.h"
#include "Qt/TSP_QtGlobalMacros.h"

// qt
#include <QMessageBox>

//---------------------------------------------------------------------------
// TSP_PageListModel
//---------------------------------------------------------------------------
TSP_PageListModel::TSP_PageListModel(TSP_Application* pApp, QObject* pParent) :
    QAbstractListModel(pParent),
    m_pApp(pApp)
{}
//---------------------------------------------------------------------------
TSP_PageListModel::~TSP_PageListModel()
{}
//---------------------------------------------------------------------------
TSP_Item* TSP_PageListModel::GetPageOwner() const
{
    return m_pPageOwner;
}
//---------------------------------------------------------------------------
void TSP_PageListModel::SetPageOwner(TSP_Item* pPageOwner)
{
    m_pPageOwner = pPageOwner;
}
//---------------------------------------------------------------------------
QString TSP_PageListModel::queryPageOwnerUID() const
{
    if (!m_pPageOwner)
        return QString();

    return QString::fromStdString(m_pPageOwner->GetUID());
}
//---------------------------------------------------------------------------
void TSP_PageListModel::onAddPageClicked()
{
    M_TRY
    {
        if (!addPage())
        {
            //: Add page error dialog title
            //% "Add a page"
            const QString title = qtTrId("id-error-add-page-title");

            //: Add page error dialog message
            //% "Failed to add the page."
            const QString msg = qtTrId("id-error-add-page-msg");

            ShowError(title, msg);
        }
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_PageListModel::onDeletePageClicked()
{
    M_TRY
    {
        if (!deletePage())
        {
            //: Delete page error dialog title
            //% "Delete a page"
            const QString title = qtTrId("id-error-delete-page-title");

            //: Delete page error dialog message
            //% "Failed to delete the page."
            const QString msg = qtTrId("id-error-delete-page-msg");

            ShowError(title, msg);
        }
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_PageListModel::onProcessDblClicked(const QString& uid)
{
    M_TRY
    {
    }
    M_CATCH_QT_MSG
}
//---------------------------------------------------------------------------
void TSP_PageListModel::clear()
{
    // reset the selected page item
    m_SelectedPageItem = -1;

    // notify the view that no page is selected
    emit showSelectedPage(m_SelectedPageItem, QString());

    // clear the model
    beginResetModel();
    m_pPageOwner = nullptr;
    endResetModel();
}
//---------------------------------------------------------------------------
bool TSP_PageListModel::addPage()
{
    // get the document
    TSP_QmlDocument* pDocument = GetDocument();

    // document exists?
    if (!pDocument)
    {
        M_LogErrorT("addPage - FAILED - no document defined");
        return false;
    }

    // is document opened?
    if (pDocument->GetStatus() == TSP_Document::IEDocStatus::IE_DS_Closed)
    {
        M_LogErrorT("addPage - FAILED - cannot add a page in a closed document");
        return false;
    }

    // page owner defined?
    if (!m_pPageOwner)
    {
        M_LogErrorT("addPage - FAILED - no atlas or process selected");
        return false;
    }

    // get page owner as atlas
    TSP_QmlAtlas* pQmlAtlas = dynamic_cast<TSP_QmlAtlas*>(m_pPageOwner);

    // succeeded?
    if (pQmlAtlas)
    {
        const int count = rowCount();

        beginInsertRows(QModelIndex(), count, count);

        // add a page to the selected atlas
        TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(pQmlAtlas->CreateAndAddPage());

        if (!pQmlPage)
        {
            M_LogErrorT("addPage - FAILED - could not add the page to the document");
            endInsertRows();
            return false;
        }

        endInsertRows();

        return true;
    }

    // FIXME test if page owner is a process and add page on it if yes

    M_LogErrorT("addPage - FAILED - unknown page owner - id - " << m_pPageOwner->GetUID());
    return false;
}
//---------------------------------------------------------------------------
bool TSP_PageListModel::deletePage()
{
    // get the document
    TSP_QmlDocument* pDocument = GetDocument();

    // document exists?
    if (!pDocument)
    {
        M_LogErrorT("deletePage - FAILED - no document defined");
        return false;
    }

    // is document opened?
    if (pDocument->GetStatus() == TSP_Document::IEDocStatus::IE_DS_Closed)
    {
        M_LogErrorT("deletePage - FAILED - cannot add a page in a closed document");
        return false;
    }

    // page owner defined?
    if (!m_pPageOwner)
    {
        M_LogErrorT("deletePage - FAILED - no atlas or process selected");
        return false;
    }

    // get page owner as atlas
    TSP_QmlAtlas* pQmlAtlas = dynamic_cast<TSP_QmlAtlas*>(m_pPageOwner);

    // succeeded?
    if (pQmlAtlas)
    {
        int count = rowCount();

        // is index out of bounds?
        if (m_SelectedPageItem < 0 || m_SelectedPageItem >= count)
            return false;

        beginRemoveRows(QModelIndex(), m_SelectedPageItem, m_SelectedPageItem);

        // remove the selected page from the selected atlas
        pQmlAtlas->RemovePage(m_SelectedPageItem);

        endRemoveRows();

        // get the new count
        count = rowCount();

        // correct the selected page item if out of bounds
        if (m_SelectedPageItem >= count)
            --m_SelectedPageItem;
        else
        if (!count)
            m_SelectedPageItem = -1;

        // change the page on the user interface
        emit showSelectedPage(m_SelectedPageItem, m_SelectedPageItem >= 0 ? GetSelectedPageUID() : QString());

        return true;
    }

    // FIXME test if page owner is a process and add page on it if yes

    M_LogErrorT("deletePage - FAILED - unknown page owner - id - " << m_pPageOwner->GetUID());
    return false;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageListModel::GetPage(int index) const
{
    if (!m_pPageOwner)
        return nullptr;

    // is index out of bounds?
    if (index < 0 || index >= rowCount())
        return nullptr;

    // get page owner as atlas
    TSP_QmlAtlas* pQmlAtlas = dynamic_cast<TSP_QmlAtlas*>(m_pPageOwner);

    // found it?
    if (pQmlAtlas)
        // get page
        return static_cast<TSP_QmlPage*>(pQmlAtlas->GetPage(index));

    // FIXME test if page owner is a process and add page on it if yes

    M_LogErrorT("GetSelectedPage - FAILED - unknown page owner - id - " << m_pPageOwner->GetUID());
    return nullptr;
}
//---------------------------------------------------------------------------
QString TSP_PageListModel::getPageName(int index) const
{
    // get page matching with index
    TSP_Page* pPage = GetPage(index);

    // found it?
    if (!pPage)
    {
        M_LogErrorT("getPageName - FAILED - page not found - index - " << index);
        return QString();
    }

    // get page name
    return QString::fromStdWString(pPage->GetName());
}
//---------------------------------------------------------------------------
TSP_Page* TSP_PageListModel::GetSelectedPage() const
{
    return GetPage(m_SelectedPageItem);
}
//---------------------------------------------------------------------------
int TSP_PageListModel::getSelectedPageIndex() const
{
    return m_SelectedPageItem;
}
//---------------------------------------------------------------------------
QString TSP_PageListModel::GetSelectedPageUID() const
{
    // get the selected page
    TSP_Page* pPage = GetSelectedPage();

    // found it?
    if (!pPage)
        return QString();

    // return page unique identifier
    return QString::fromStdString(pPage->GetUID());
}
//---------------------------------------------------------------------------
void TSP_PageListModel::onPageSelected(int index)
{
    // do nothing if the current page doesn't change
    if (m_SelectedPageItem == index)
        return;

    // get row count
    const int count = rowCount();

    // is index out of bounds?
    if (index < 0 || index >= count)
    {
        M_LogErrorT("onPageSelected - FAILED - index is out of bounds - index - " << index << " - count - " << count);

        // no selected item
        m_SelectedPageItem = -1;
    }
    else
        // update selected item
        m_SelectedPageItem = index;

    // change the page on the user interface
    emit showSelectedPage(m_SelectedPageItem, m_SelectedPageItem >= 0 ? GetSelectedPageUID() : QString());
}
//---------------------------------------------------------------------------
int TSP_PageListModel::rowCount(const QModelIndex& pParent) const
{
    if (!m_pPageOwner)
        return 0;

    // get page owner as atlas
    TSP_QmlAtlas* pQmlAtlas = dynamic_cast<TSP_QmlAtlas*>(m_pPageOwner);

    // found it?
    if (pQmlAtlas)
        return pQmlAtlas->GetPageCount();

    // FIXME test if page owner is a process and add page on it if yes

    M_LogErrorT("addPage - FAILED - unknown page owner - id - " << m_pPageOwner->GetUID());
    return 0;
}
//---------------------------------------------------------------------------
QVariant TSP_PageListModel::data(const QModelIndex& index, int role) const
{
    // search for page item data role to get
    switch ((TSP_PageListModel::IEDataRole)role)
    {
        case TSP_PageListModel::IEDataRole::IE_DR_PageName:
            return getPageName(index.row());
    }

    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> TSP_PageListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[(int)TSP_PageListModel::IEDataRole::IE_DR_PageName] = "pageName";

    return roles;
}
//---------------------------------------------------------------------------
TSP_QmlDocument* TSP_PageListModel::GetDocument() const
{
    // no application?
    if (!m_pApp)
        return nullptr;

    // get document
    return m_pApp->GetDocument();
}
//---------------------------------------------------------------------------
void TSP_PageListModel::ShowError(const QString& title, const QString& msg)
{
    // no application?
    if (!m_pApp)
        return;

    TSP_MainFormModel* pMainFormModel = m_pApp->GetMainFormModel();

    // no main form model?
    if (!pMainFormModel)
        return;

    pMainFormModel->showError(title, msg);
}
//---------------------------------------------------------------------------
