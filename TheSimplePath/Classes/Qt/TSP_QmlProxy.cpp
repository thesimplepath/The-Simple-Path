/****************************************************************************
 * ==> TSP_QmlProxy --------------------------------------------------------*
 ****************************************************************************
 * Description:  Proxy between an UI component and its c++ representation   *
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

#include "TSP_QmlProxy.h"

// qt classes
#include "TSP_QmlProxyDictionary.h"

//---------------------------------------------------------------------------
// TSP_QmlProxy
//---------------------------------------------------------------------------
TSP_QmlProxy::TSP_QmlProxy(QObject* pParent) :
    QObject(pParent)
{}
//---------------------------------------------------------------------------
TSP_QmlProxy::~TSP_QmlProxy()
{
    TSP_QmlProxyDictionary::Instance()->Unregister(m_UID);
}
//---------------------------------------------------------------------------
QString TSP_QmlProxy::getUID() const
{
    return QString::fromStdString(m_UID);
}
//---------------------------------------------------------------------------
void TSP_QmlProxy::setUID(const QString& uid)
{
    m_UID = uid.toStdString();

    // register the instance in the document item dictionary
    TSP_QmlProxyDictionary::Instance()->Register(m_UID, this);
}
//---------------------------------------------------------------------------
