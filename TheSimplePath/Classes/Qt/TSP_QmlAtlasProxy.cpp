/****************************************************************************
 * ==> TSP_QmlAtlasProxy ---------------------------------------------------*
 ****************************************************************************
 * Description:  Atlas proxy between qml view and application engine        *
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

#include "TSP_QmlAtlasProxy.h"

// qt classes
#include "TSP_QmlAtlas.h"

//---------------------------------------------------------------------------
// TSP_QmlAtlasProxy
//---------------------------------------------------------------------------
TSP_QmlAtlasProxy::TSP_QmlAtlasProxy(QObject* pParent) :
    TSP_QmlProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlasProxy::~TSP_QmlAtlasProxy()
{}
//---------------------------------------------------------------------------
QString TSP_QmlAtlasProxy::getName() const
{
    if (!m_pAtlas)
        return "";

    return QString::fromStdWString(m_pAtlas->GetName());
}
//---------------------------------------------------------------------------
void TSP_QmlAtlasProxy::setName(const QString& name)
{
    if (!m_pAtlas)
        return;

    m_pAtlas->SetName(name.toStdWString());
}
//---------------------------------------------------------------------------
TSP_QmlAtlas* TSP_QmlAtlasProxy::GetAtlas() const
{
    return m_pAtlas;
}
//---------------------------------------------------------------------------
void TSP_QmlAtlasProxy::SetAtlas(TSP_QmlAtlas* pAtlas)
{
    m_pAtlas = pAtlas;
}
//---------------------------------------------------------------------------
bool TSP_QmlAtlasProxy::AddPage(const QString& uid)
{
    m_PageAdded = false;

    emit addPageToView(uid);

    return m_PageAdded;
}
//---------------------------------------------------------------------------
void TSP_QmlAtlasProxy::RemovePage(const QString& uid)
{
    emit removePageFromView(uid);
}
//---------------------------------------------------------------------------
void TSP_QmlAtlasProxy::onPageAdded(bool success)
{
    m_PageAdded = success;
}
//---------------------------------------------------------------------------
