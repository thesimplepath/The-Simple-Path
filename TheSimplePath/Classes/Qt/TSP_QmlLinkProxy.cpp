/****************************************************************************
 * ==> TSP_QmlLinkProxy ----------------------------------------------------*
 ****************************************************************************
 * Description:  Link proxy between qml view and application engine         *
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

#include "TSP_QmlLinkProxy.h"

 // core classes
#include "Core/TSP_Link.h"

//---------------------------------------------------------------------------
// TSP_QmlLinkProxy
//---------------------------------------------------------------------------
TSP_QmlLinkProxy::TSP_QmlLinkProxy(QObject* pParent) :
    TSP_QmlProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_QmlLinkProxy::~TSP_QmlLinkProxy()
{}
//---------------------------------------------------------------------------
QString TSP_QmlLinkProxy::getTitle() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetTitle());
}
//---------------------------------------------------------------------------
QString TSP_QmlLinkProxy::getDescription() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetDescription());
}
//---------------------------------------------------------------------------
QString TSP_QmlLinkProxy::getComments() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetComments());
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setTitle(const QString& title)
{
    if (!m_pLink)
        return;

    m_pLink->SetTitle(title.toStdWString());

    emit titleChanged(title);
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setDescription(const QString& description)
{
    if (!m_pLink)
        return;

    m_pLink->SetDescription(description.toStdWString());

    emit descriptionChanged(description);
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setComments(const QString& comments)
{
    if (!m_pLink)
        return;

    m_pLink->SetComments(comments.toStdWString());

    emit commentsChanged(comments);
}
//---------------------------------------------------------------------------
TSP_Link* TSP_QmlLinkProxy::GetLink() const
{
    return m_pLink;
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::SetLink(TSP_Link* pLink)
{
    m_pLink = pLink;
}
//---------------------------------------------------------------------------
