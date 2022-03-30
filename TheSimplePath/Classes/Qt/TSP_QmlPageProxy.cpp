/****************************************************************************
 * ==> TSP_QmlPageProxy ----------------------------------------------------*
 ****************************************************************************
 * Description:  Page proxy between qml view and application engine         *
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

#include "TSP_QmlPageProxy.h"

// core classes
#include "Core\TSP_Page.h"

// qt classes
#include "TSP_QmlPage.h"

//---------------------------------------------------------------------------
// TSP_QmlPageProxy
//---------------------------------------------------------------------------
TSP_QmlPageProxy::TSP_QmlPageProxy(QObject* pParent) :
    TSP_QmlProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_QmlPageProxy::~TSP_QmlPageProxy()
{}
//---------------------------------------------------------------------------
QString TSP_QmlPageProxy::getName() const
{
    if (!m_pPage)
        return "";

    return QString::fromStdWString(m_pPage->GetName());
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::setName(const QString& name)
{
    if (!m_pPage)
        return;

    m_pPage->SetName(name.toStdWString());

    emit nameChanged(name);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlPageProxy::GetPage() const
{
    return m_pPage;
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::SetPage(TSP_Page* pPage)
{
    m_pPage = pPage;
}
//---------------------------------------------------------------------------
bool TSP_QmlPageProxy::AddBox(const QString&      type,
                              const QString&      uid,
                                    IEBoxPosition position,
                                    int           x,
                                    int           y,
                                    int           width,
                                    int           height)
{
    m_BoxAdded = false;

    emit addBoxToView(type, uid, (int)position, x, y, width, height);

    return m_BoxAdded;
}
//---------------------------------------------------------------------------
bool TSP_QmlPageProxy::AddLink(const QString&               type,
                               const QString&               uid,
                               const QString&               startUID,
                                     TSP_QmlBox::IEPosition startPos,
                               const QString&               endUID,
                                     TSP_QmlBox::IEPosition endPos,
                                     int                    x,
                                     int                    y,
                                     int                    width,
                                     int                    height)
{
    m_LinkAdded = false;

    emit addLinkToView(type, uid, startUID, (int)startPos, endUID, (int)endPos, x, y, width, height);

    return m_LinkAdded;
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::RemoveComponent(const QString& uid)
{
    emit removeComponentView(uid);
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::onBoxAdded(bool success)
{
    m_BoxAdded = success;
}
//---------------------------------------------------------------------------
QString TSP_QmlPageProxy::onAddLinkStart(const QString& fromUID, int position)
{
    if (!m_pPage)
        return "";

    // get the page
    TSP_QmlPage* pQmlPage = static_cast<TSP_QmlPage*>(m_pPage);

    // found it?
    if (!pQmlPage)
        return "";

    //: New link title
    //% "New link"
    const QString defLinkTitle = qtTrId("id-new-link-title");

    // create and add a new link in the page
    TSP_Link* pLink = pQmlPage->CreateAndAddLink(defLinkTitle.toStdWString(),
                                                 L"",
                                                 L"",
                                                 fromUID.toStdWString(),
                                                 (TSP_QmlBox::IEPosition)position);

    // succeeded?
    if (!pLink)
        return "";

    // get newly added link unique identifier
    return QString::fromStdString(pLink->GetUID());
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::onLinkAdded(bool success)
{
    m_LinkAdded = success;
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::onDeleteBox(const QString& uid)
{
    if (uid.isEmpty())
        return;

    if (!m_pPage)
        return;

    // remove the box from page
    m_pPage->Remove(uid.toStdString());
}
//---------------------------------------------------------------------------
void TSP_QmlPageProxy::onDeleteLink(const QString& uid)
{
    if (uid.isEmpty())
        return;

    if (!m_pPage)
        return;

    // remove the link from page
    m_pPage->Remove(uid.toStdString());
}
//---------------------------------------------------------------------------
