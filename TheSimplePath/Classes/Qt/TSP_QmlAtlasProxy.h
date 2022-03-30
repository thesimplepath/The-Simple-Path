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

#pragma once

// qt classes
#include "TSP_QmlProxy.h"

// qt
#include <QObject>
#include <QVariant>

// class prototypes
class TSP_QmlAtlas;

/**
* Atlas proxy
*@author Jean-Milost Reymond
*/
class TSP_QmlAtlasProxy : public TSP_QmlProxy
{
    Q_OBJECT

    public:
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

    public slots:
        /**
        * Gets the atlas name
        *@return the atlas name
        */
        virtual QString getName() const;

        /**
        * Sets the atlas name
        *@param name - the atlas name
        */
        virtual void setName(const QString& name);

    signals:
        /**
        * Called when the name changed
        *@param name - name
        */
        void nameChanged(const QString& name);

        /**
        * Called when a page is added to the view
        *@param uid - page unique identifier
        */
        void addPageToView(const QString& uid);

        /**
        * Called when a page is removed from the view
        *@param uid - page unique identifier
        */
        void removePageFromView(const QString& uid);

        /**
        * Called when the selected page unique identifier is queried
        */
        void querySelectedPageUID();

        /**
        * Called when the selected page owner unique identifier is queried
        */
        void querySelectedPageOwnerUID();

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlAtlasProxy(QObject* pParent = nullptr);

        virtual ~TSP_QmlAtlasProxy();

        /**
        * Gets the linked atlas
        *@return the linked atlas, nullptr if no atlas
        */
        virtual TSP_QmlAtlas* GetAtlas() const;

        /**
        * Sets the linked atlas
        *@param pAtlas - the linked atlas
        */
        virtual void SetAtlas(TSP_QmlAtlas* pAtlas);

        /**
        * Adds a new page on the atlas
        *@param uid - page unique identifier
        *@return true on success, otherwise false
        */
        virtual bool AddPage(const QString& uid);

        /**
        * Removes a page from the atlas
        *@param uid - page unique identifier
        */
        virtual void RemovePage(const QString& uid);

        /**
        * Queries the selected page unique identifier
        *@return the selected page unique identifier
        */
        virtual QString QuerySelectedPageUID();

        /**
        * Queries the page owner unique identifier currently selected on the interface
        *@return the selected page index
        */
        virtual QString QuerySelectedPageOwnerUID();

        /**
        * Notify that a page was added
        *@param success - if true, the page was added successfully
        */
        virtual Q_INVOKABLE void onPageAdded(bool success);

        /**
        * Notify that a the selected page unique identifier was queried
        *@param uid - the selected page unique identifier, empty string if no page selected
        */
        virtual Q_INVOKABLE void onSelectedPageUIDQueried(const QString& uid);

        /**
        * Notify that the selected page owner unique identifier was queried
        *@param uid - the selected page owner unique identifier, empty string if no page owner currently selected on the interface
        */
        virtual Q_INVOKABLE void onSelectedPageOwnerUIDQueried(const QString& uid);

    private:
        TSP_QmlAtlas* m_pAtlas               = nullptr;
        QString       m_SelectedPageUID;
        QString       m_SelectedPageOwnerUID;
        bool          m_PageAdded            = false;
};
