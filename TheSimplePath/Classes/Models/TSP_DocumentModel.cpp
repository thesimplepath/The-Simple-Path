/****************************************************************************
 * ==> TSP_DocumentModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  A model for the document                                   *
 * Contained in: Models                                                     *
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

#include "TSP_DocumentModel.h"

//---------------------------------------------------------------------------
// TSP_DocumentModel
//---------------------------------------------------------------------------
TSP_DocumentModel::TSP_DocumentModel(QObject* pParent) :
    QAbstractListModel(pParent),
    m_pDocument(new TSP_Document()),
    m_pModelModel(new TSP_ModelModel(pParent))
{}
//---------------------------------------------------------------------------
TSP_DocumentModel::~TSP_DocumentModel()
{
    if (m_pModelModel)
        delete m_pModelModel;

    if (m_pDocument)
        delete m_pDocument;
}
//---------------------------------------------------------------------------
TSP_Document* TSP_DocumentModel::GetDocument() const
{
    return m_pDocument;
}
//---------------------------------------------------------------------------
TSP_ModelModel* TSP_DocumentModel::GetModelModel() const
{
    return m_pModelModel;
}
//---------------------------------------------------------------------------
void TSP_DocumentModel::addModel(const QString& name)
{
    if (!m_pDocument)
        return;

    const int count = rowCount();

    beginInsertRows(QModelIndex(), count, count);
    m_pDocument->AddModel(name.toStdWString());
    endInsertRows();
}
//---------------------------------------------------------------------------
void TSP_DocumentModel::removeModel(std::size_t index)
{
    if (!m_pDocument)
        return;

    const int count = rowCount();

    if (!count)
        return;

    beginRemoveRows(QModelIndex(), count - 1, count - 1);
    m_pDocument->RemoveModel(index);
    endRemoveRows();
}
//---------------------------------------------------------------------------
int TSP_DocumentModel::rowCount(const QModelIndex& pParent) const
{
    if (!m_pDocument)
        return 0;

    return m_pDocument->GetModelCount();
}
//---------------------------------------------------------------------------
QVariant TSP_DocumentModel::data(const QModelIndex& index, int role) const
{
    if (!m_pDocument)
        return QVariant();

    // search for document data role to get (i.e not dependent from index)
    switch ((TSP_DocumentModel::IEDataRole)role)
    {
        case TSP_DocumentModel::IEDataRole::IE_DR_Title:
            // get the title
            return QString::fromStdWString(m_pDocument->GetTitle());
    }

    // get current index
    const int currentIndex = index.row();

    // is index out of bounds?
    if (currentIndex < 0 || (std::size_t)currentIndex > m_pDocument->GetModelCount())
        return QVariant();

    // search for model data role to get
    switch ((TSP_DocumentModel::IEDataRole)role)
    {
        case TSP_DocumentModel::IEDataRole::IE_DR_ModelName:
        {
            // get the model matching with row index
            TSP_Model* pModel = m_pDocument->GetModel(currentIndex);

            // found it?
            if (!pModel)
                return QVariant();

            // get the model name
            return QString::fromStdWString(pModel->GetName());
        }
    }

    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> TSP_DocumentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[(int)TSP_DocumentModel::IEDataRole::IE_DR_Title]     = "title";
    roles[(int)TSP_DocumentModel::IEDataRole::IE_DR_ModelName] = "modelName";

    return roles;
}
//---------------------------------------------------------------------------
