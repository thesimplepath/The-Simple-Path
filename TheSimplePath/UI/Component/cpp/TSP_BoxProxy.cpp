/****************************************************************************
 * ==> TSP_BoxProxy --------------------------------------------------------*
 ****************************************************************************
 * Description:  Proxy between a box on the UI and its c++ representation   *
 * Contained in: Component                                                  *
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

#include "TSP_BoxProxy.h"

//---------------------------------------------------------------------------
// TSP_BoxProxy
//---------------------------------------------------------------------------
TSP_BoxProxy::TSP_BoxProxy(QObject* pParent) :
    TSP_ComponentProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_BoxProxy::~TSP_BoxProxy()
{}
//---------------------------------------------------------------------------
QString TSP_BoxProxy::getTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
QString TSP_BoxProxy::getDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
QString TSP_BoxProxy::getComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void TSP_BoxProxy::setTitle(const QString& title)
{
    m_Title = title;

    emit titleChanged(m_Title);
}
//---------------------------------------------------------------------------
void TSP_BoxProxy::setDescription(const QString& description)
{
    m_Description = description;

    emit descriptionChanged(m_Description);
}
//---------------------------------------------------------------------------
void TSP_BoxProxy::setComments(const QString& comments)
{
    m_Comments = comments;

    emit commentsChanged(m_Comments);
}
//---------------------------------------------------------------------------
