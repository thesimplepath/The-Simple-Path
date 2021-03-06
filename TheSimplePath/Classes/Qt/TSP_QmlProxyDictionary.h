/****************************************************************************
 * ==> TSP_QmlProxyDictionary ----------------------------------------------*
 ****************************************************************************
 * Description:  Provides a qml proxy dictionary                            *
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

#pragma once

// std
#include <map>
#include <mutex>

/**
* Provides a qml proxy dictionary
*@author Jean-Milost Reymond
*/
class TSP_QmlProxyDictionary
{
    public:
        /**
        * Gets the dictionary instance, creates it if still not exists
        *@return the dictionary instance
        *@throw exception if instance could not be created
        */
        static TSP_QmlProxyDictionary* Instance();

        /**
        * Releases the dictionary instance
        */
        static void Release();

        /**
        * Registers a proxy in the dictionary
        *@param uid - item unique identifier
        *@aram pProxy - proxy to register
        */
        void Register(const std::string& uid, void* pProxy);

        /**
        * Unregisters an item from the document dictionary
        *@param uid - proxy unique identifier to unregister
        */
        void Unregister(const std::string& uid);

        /**
        * Unregisters an item from the document dictionary
        *@param pProxy - proxy to unregister
        */
        void Unregister(void* pProxy);

        /**
        * Gets the proxy object
        *@param uid - proxy unique identifier to get
        *@return proxy, nullptr if not found or on error
        */
        void* GetProxy(const std::string& uid) const;

        /**
        * Gets the proxy uid
        *@param proxy - proxy for which the unique identifier should be get
        *@return proxy uid, empty string if not found or on error
        */
        std::string GetUID(void* pProxy) const;

        /**
        * Logs the proxy dictionary content
        */
        #ifdef _DEBUG
            void Log() const;
        #endif

    private:
        /**
        * Instance class, needed to allow unique_ptr usage despite of singleton privacy and without
        * declare unique_ptr friend
        */
        struct IInstance
        {
            TSP_QmlProxyDictionary* m_pInstance = nullptr;

            IInstance();
            virtual ~IInstance();
        };

        typedef std::map<std::string, void*> IDictionary;
        typedef std::map<void*, std::string> IReverseDictionary;

        static std::unique_ptr<IInstance> m_pProxyDictionary;
        static std::mutex                 m_Mutex;
               IDictionary                m_Dictionary;
               IReverseDictionary         m_ReverseDictionary;

        TSP_QmlProxyDictionary();

        /**
        * Copy constructor
        *@param other - other dictionary to copy from
        */
        TSP_QmlProxyDictionary(const TSP_QmlProxyDictionary& other);

        ~TSP_QmlProxyDictionary();

        /**
        * Copy operator
        *@param other - other dictionary to copy from
        */
        const TSP_QmlProxyDictionary& operator = (const TSP_QmlProxyDictionary& other);
};
