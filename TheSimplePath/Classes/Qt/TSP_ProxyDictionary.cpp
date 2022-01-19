/****************************************************************************
 * ==> TSP_ProxyDictionary -------------------------------------------------*
 ****************************************************************************
 * Description:  Provides a proxy dictionary                                *
 * Contained in: Core                                                       *
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

#include "TSP_ProxyDictionary.h"

//---------------------------------------------------------------------------
// Static members
//---------------------------------------------------------------------------
TSP_ProxyDictionary* TSP_ProxyDictionary::m_pProxyDictionary = nullptr;
std::mutex           TSP_ProxyDictionary::m_Mutex;
//---------------------------------------------------------------------------
// TSP_ProxyDictionary
//---------------------------------------------------------------------------
TSP_ProxyDictionary::TSP_ProxyDictionary()
{}
//---------------------------------------------------------------------------
TSP_ProxyDictionary::TSP_ProxyDictionary(const TSP_ProxyDictionary& other)
{
    throw new std::exception("Cannot create a copy of a singleton class");
}
//---------------------------------------------------------------------------
TSP_ProxyDictionary::~TSP_ProxyDictionary()
{}
//---------------------------------------------------------------------------
const TSP_ProxyDictionary& TSP_ProxyDictionary::operator = (const TSP_ProxyDictionary& other)
{
    throw new std::exception("Cannot create a copy of a singleton class");

    // useless and never reached, but otherwise VS generates an error
    return *this;
}
//---------------------------------------------------------------------------
TSP_ProxyDictionary* TSP_ProxyDictionary::Instance()
{
    // check instance out of the thread lock (double check lock)
    if (!m_pProxyDictionary)
    {
        // lock up the thread
        std::unique_lock<std::mutex> lock(m_Mutex);

        // create the instance
        if (!m_pProxyDictionary)
            m_pProxyDictionary = new (std::nothrow)TSP_ProxyDictionary();
    }

    // still not created?
    if (!m_pProxyDictionary)
        throw new std::exception("Could not create the document item dictionary unique instance");

    return m_pProxyDictionary;
}
//---------------------------------------------------------------------------
void TSP_ProxyDictionary::Release()
{
    // lock up the thread
    std::unique_lock<std::mutex> lock(m_Mutex);

    if (!m_pProxyDictionary)
        return;

    // delete the instance
    delete m_pProxyDictionary;
    m_pProxyDictionary = nullptr;
}
//---------------------------------------------------------------------------
void TSP_ProxyDictionary::Register(const std::string& uid, void* pProxy)
{
    if (uid.empty())
        return;

    if (!pProxy)
        return;

    IDictionary::iterator it = m_Dictionary.find(uid);

    if (it != m_Dictionary.end())
        it->second = pProxy;
    else
        m_Dictionary[uid] = pProxy;

    IReverseDictionary::iterator itReverse = m_ReverseDictionary.find(pProxy);

    if (itReverse != m_ReverseDictionary.end())
        itReverse->second = uid;
    else
        m_ReverseDictionary[pProxy] = uid;
}
//---------------------------------------------------------------------------
void TSP_ProxyDictionary::Unregister(const std::string& uid)
{
    if (uid.empty())
        return;

    void* pProxy = nullptr;

    IDictionary::iterator it = m_Dictionary.find(uid);

    if (it != m_Dictionary.end())
    {
        pProxy = it->second;
        m_Dictionary.erase(it);
    }

    if (!pProxy)
        return;

    IReverseDictionary::iterator itReverse = m_ReverseDictionary.find(pProxy);

    if (itReverse != m_ReverseDictionary.end())
        m_ReverseDictionary.erase(itReverse);
}
//---------------------------------------------------------------------------
void TSP_ProxyDictionary::Unregister(void* pProxy)
{
    if (!pProxy)
        return;

    std::string uid;

    IReverseDictionary::iterator itReverse = m_ReverseDictionary.find(pProxy);

    if (itReverse != m_ReverseDictionary.end())
    {
        uid = itReverse->second;
        m_ReverseDictionary.erase(itReverse);
    }

    if (uid.empty())
        return;

    IDictionary::iterator it = m_Dictionary.find(uid);

    if (it != m_Dictionary.end())
        m_Dictionary.erase(it);
}
//---------------------------------------------------------------------------
void* TSP_ProxyDictionary::GetProxy(const std::string& uid) const
{
    IDictionary::const_iterator it = m_Dictionary.find(uid);

    if (it != m_Dictionary.end())
        return it->second;

    return nullptr;
}
//---------------------------------------------------------------------------
std::string TSP_ProxyDictionary::GetUID(void* pProxy) const
{
    IReverseDictionary::const_iterator it = m_ReverseDictionary.find(pProxy);

    if (it != m_ReverseDictionary.end())
        return it->second;

    return "";
}
//---------------------------------------------------------------------------
