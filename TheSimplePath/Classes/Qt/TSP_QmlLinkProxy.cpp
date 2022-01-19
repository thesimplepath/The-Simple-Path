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
    return m_Title;
}
//---------------------------------------------------------------------------
QString TSP_QmlLinkProxy::getDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
QString TSP_QmlLinkProxy::getComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setTitle(const QString& title)
{
    m_Title = title;

    emit titleChanged(m_Title);
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setDescription(const QString& description)
{
    m_Description = description;

    emit descriptionChanged(m_Description);
}
//---------------------------------------------------------------------------
void TSP_QmlLinkProxy::setComments(const QString& comments)
{
    m_Comments = comments;

    emit commentsChanged(m_Comments);
}
//---------------------------------------------------------------------------
