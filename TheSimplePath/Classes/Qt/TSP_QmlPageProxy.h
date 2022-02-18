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

#pragma once

// qt classes
#include "TSP_QmlProxy.h"

// qt
#include <QObject>

// classes prototypes
class TSP_Page;

/**
* Page proxy
*@author Jean-Milost Reymond
*/
class TSP_QmlPageProxy : public TSP_QmlProxy
{
    Q_OBJECT

    public:
        /**
        * Box default position type
        *@note This enum is linked with the one located in TSP_PageView.
        *      Don't modify it without updating its twin
        */
        enum class IEBoxPosition
        {
            IE_BP_Default = 0,
            IE_BP_Centered,
            IE_BP_Custom
        };

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
        void nameChanged(const QString& name);
        void addBoxToView(const QString& type, const QString& uid, int position, int x, int y);

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlPageProxy(QObject* pParent = nullptr);

        virtual ~TSP_QmlPageProxy();

        /**
        * Gets the linked page
        *@return the linked page, nullptr if no page
        */
        virtual TSP_Page* GetPage() const;

        /**
        * Sets the linked page
        *@param pPage - the linked page
        */
        virtual void SetPage(TSP_Page* pPage);

        /**
        * Adds a box on the page
        *@param type - box type
        *@param uid - box unique identifier
        *@param position - default position where the box will appear
        *@param x - box x position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param y - box y position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@return true on success, otherwise false
        */
        virtual bool AddBox(const QString& type, const QString& uid, IEBoxPosition position, int x, int y);

        /**
        * Notify that a box was added
        *@param success - if true, the box was added successfully
        */
        virtual Q_INVOKABLE void onBoxAdded(bool success);

        /**
        * Notify that a link started to be added
        *@param fromUID - box unique identifier from which the link is added
        *@param position - box connector position
        *@return link unique identifier, empty string on error
        */
        virtual Q_INVOKABLE QString onAddLinkStart(const QString& fromUID, int position);

    private:
        TSP_Page* m_pPage    = nullptr;
        bool      m_BoxAdded = false;
};
