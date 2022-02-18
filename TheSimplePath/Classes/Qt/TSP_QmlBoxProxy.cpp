/****************************************************************************
 * ==> TSP_QmlBoxProxy -----------------------------------------------------*
 ****************************************************************************
 * Description:  Box proxy between qml view and application engine          *
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

#include "TSP_QmlBoxProxy.h"

 // core classes
#include "Core/TSP_Box.h"

//---------------------------------------------------------------------------
// TSP_QmlBoxProxy
//---------------------------------------------------------------------------
TSP_QmlBoxProxy::TSP_QmlBoxProxy(QObject* pParent) :
    TSP_QmlProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_QmlBoxProxy::~TSP_QmlBoxProxy()
{}
//---------------------------------------------------------------------------
QString TSP_QmlBoxProxy::getTitle() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetTitle());
}
//---------------------------------------------------------------------------
QString TSP_QmlBoxProxy::getDescription() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetDescription());
}
//---------------------------------------------------------------------------
QString TSP_QmlBoxProxy::getComments() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetComments());
}
//---------------------------------------------------------------------------
void TSP_QmlBoxProxy::setTitle(const QString& title)
{
    if (!m_pBox)
        return;

    m_pBox->SetTitle(title.toStdWString());

    emit titleChanged(title);
}
//---------------------------------------------------------------------------
void TSP_QmlBoxProxy::setDescription(const QString& description)
{
    if (!m_pBox)
        return;

    m_pBox->SetDescription(description.toStdWString());

    emit descriptionChanged(description);
}
//---------------------------------------------------------------------------
void TSP_QmlBoxProxy::setComments(const QString& comments)
{
    if (!m_pBox)
        return;

    m_pBox->SetComments(comments.toStdWString());

    emit commentsChanged(comments);
}
//---------------------------------------------------------------------------
TSP_Box* TSP_QmlBoxProxy::GetBox() const
{
    return m_pBox;
}
//---------------------------------------------------------------------------
void TSP_QmlBoxProxy::SetBox(TSP_Box* pBox)
{
    m_pBox = pBox;
}
//---------------------------------------------------------------------------
