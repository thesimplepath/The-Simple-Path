/****************************************************************************
 * ==> TSP_ComponentProxy --------------------------------------------------*
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

#include "TSP_ComponentProxy.h"

// component classes
#include "TSP_ProxyDictionary.h"

//---------------------------------------------------------------------------
// TSP_ComponentProxy
//---------------------------------------------------------------------------
TSP_ComponentProxy::TSP_ComponentProxy(QObject* pParent) :
    QObject(pParent)
{
    // use the pointer itself as unique identifier
    m_UID = std::to_string(std::uintptr_t(this));

    // register the instance in the document item dictionary
    TSP_ProxyDictionary::Instance()->Register(m_UID, this);
}
//---------------------------------------------------------------------------
TSP_ComponentProxy::~TSP_ComponentProxy()
{
    TSP_ProxyDictionary::Instance()->Unregister(m_UID);
}
//---------------------------------------------------------------------------
QString TSP_ComponentProxy::getUID() const
{
    return QString::fromStdString(m_UID);
}
//---------------------------------------------------------------------------
