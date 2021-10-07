/****************************************************************************
 * ==> TSP_ModelModel ------------------------------------------------------*
 ****************************************************************************
 * Description:  A model for the business models                            *
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

#include "TSP_ModelModel.h"

//---------------------------------------------------------------------------
// TSP_ModelModel
//---------------------------------------------------------------------------
TSP_ModelModel::TSP_ModelModel(QObject* pParent) :
    QAbstractListModel(pParent)
{}
//---------------------------------------------------------------------------
TSP_ModelModel::~TSP_ModelModel()
{}
//---------------------------------------------------------------------------
int TSP_ModelModel::rowCount(const QModelIndex& pParent) const
{
    /*REM FIXME
    if (!m_pDocument)
        return 0;

    return m_pDocument->GetModelCount();
    */
    return 0;
}
//---------------------------------------------------------------------------
QVariant TSP_ModelModel::data(const QModelIndex& index, int role) const
{
    /*REM FIXME
    if (!m_pDocument)
        return QVariant();

    // get current index
    const int currentIndex = index.row();

    // is index out of bounds?
    if (currentIndex < 0 || (std::size_t)currentIndex > m_pDocument->GetModelCount())
        return QVariant();

    // search for data role to get
    switch ((TSP_DocumentModel::IEDataRole)role)
    {
        case TSP_DocumentModel::IEDataRole::IE_DR_Name:
        {
            // get the model matching with row index
            TSP_Model* pModel = m_pDocument->GetModel(currentIndex);

            // found it?
            if (!pModel)
                return QVariant();

            // get the model name
            return QString::fromStdWString(pModel->GetName());
        }

        default:
            return QVariant();
    }
    */
    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> TSP_ModelModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    //REM FIXME roles[(int)TSP_DocumentModel::IEDataRole::IE_DR_Name] = "name";

    return roles;
}
//---------------------------------------------------------------------------
