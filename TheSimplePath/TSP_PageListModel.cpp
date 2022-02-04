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
void TSP_PageListModel::onAddPageClicked()
{
    addPage();
}
//---------------------------------------------------------------------------
void TSP_PageListModel::onDeletePageClicked()
{
    emit testSignal();
}
//---------------------------------------------------------------------------
void TSP_PageListModel::addPage()
{
    const int count = rowCount();

    beginInsertRows(QModelIndex(), count, count);
    ++m_TempCount;
    endInsertRows();
}
//---------------------------------------------------------------------------
QString TSP_PageListModel::getPageName(int index) const
{
    return "Item " + QString::number(index);
}
//---------------------------------------------------------------------------
int TSP_PageListModel::rowCount(const QModelIndex& pParent) const
{
    return m_TempCount;
}
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::beginAddPage()
{
    const int count = rowCount();

    beginInsertRows(QModelIndex(), count, count);
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::endAddPage()
{
    endInsertRows();
}
*/
//---------------------------------------------------------------------------
/*REM
int TSP_QmlDocumentModel::getDocStatus() const
{
    if (!m_pDocument)
        return (int)TSP_Document::IEDocStatus::IE_DS_Error;

    return (int)m_pDocument->GetStatus();
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::setDocStatus(int docStatus)
{
    if (!m_pDocument)
        return;

    m_pDocument->SetStatus((TSP_Document::IEDocStatus)docStatus);
}
*/
//---------------------------------------------------------------------------
/*REM
QString TSP_QmlDocumentModel::getSelectedAtlasUID() const
{
    return m_SelectedAtlasUID;
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::setSelectedAtlasUID(QString uid)
{
    m_SelectedAtlasUID = uid;
}
*/
//---------------------------------------------------------------------------
/*REM
bool TSP_QmlDocumentModel::CreateView()
{
    if (!m_pDocument)
        return false;

    // notify the interface that a new document should be created
    emit createDocumentView(QString::fromStdWString(m_pDocument->GetTitle()),
                            (int)m_pDocument->GetOpenedCount());

    // NOTE emit is synchronous, so it's safe to test if document was opened
    return (m_pDocument->GetStatus() != TSP_Document::IEDocStatus::IE_DS_Error);
}
*/
//---------------------------------------------------------------------------
/*REM
bool TSP_QmlDocumentModel::DeleteView()
{
    if (!m_pDocument)
        return false;

    // notify the interface that the document should be deleted
    emit deleteDocumentView();

    return true;
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::addAtlas(const QString& uid)
{
    emit addAtlasToView(uid);
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::beginRemoveAtlas()
{
    const int count = rowCount();

    if (!count)
        return;

    beginRemoveRows(QModelIndex(), count - 1, count - 1);
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::endRemoveAtlas()
{
    endRemoveRows();
}
*/
//---------------------------------------------------------------------------
/*REM
void TSP_QmlDocumentModel::removeAtlas(const QString& uid)
{
    emit removeAtlasFromView(uid);
}
*/
//---------------------------------------------------------------------------
/*REM
QString TSP_QmlDocumentModel::QuerySelectedAtlasUID()
{
    // query the latest selected atlas on the document view
    emit queryAtlasUID();

    return m_SelectedAtlasUID;
}
*/
//---------------------------------------------------------------------------
//REM
//int TSP_PageListModel::rowCount(const QModelIndex& pParent) const
//{
//    /*REM
//    if (!m_pDocument)
//        return 0;
//
//    return m_pDocument->GetAtlasCount();
//    */
//    return 0;//FIXME
//}
//---------------------------------------------------------------------------
QVariant TSP_PageListModel::data(const QModelIndex& index, int role) const
{
    /*REM
    if (!m_pDocument)
        return QVariant();

    // search for document data role to get (i.e not dependent from index)
    switch ((TSP_QmlDocumentModel::IEDataRole)role)
    {
        case TSP_QmlDocumentModel::IEDataRole::IE_DR_Title:
            // get the title
            return QString::fromStdWString(m_pDocument->GetTitle());
    }
    */

    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> TSP_PageListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    //REMroles[(int)TSP_QmlDocumentModel::IEDataRole::IE_DR_Title] = "title";

    return roles;
}
//---------------------------------------------------------------------------
