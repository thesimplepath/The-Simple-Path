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
#include "TSP_QmlBox.h"

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
        /**
        * Called when the page name changed
        *@param name - page name
        */
        void nameChanged(const QString& name);

        /**
        * Called when a box is added to the page
        *@param type - box type
        *@param uid - box unique identifier
        *@param position - default position where the box will appear
        *@param x - box x position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param y - box y position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param width - link width in pixels
        *@param height - link height in pixels
        */
        void addBoxToView (const QString& type,
                           const QString& uid,
                                 int      position,
                                 int      x,
                                 int      y,
                                 int      width,
                                 int      height);

        /**
        * Called when a link is added to the page
        *@param type - link type
        *@param uid - link unique identifier
        *@param startUID - start box unique identifier from which the link is attached
        *@param startPos - start box position from which the link is attached
        *@param endUID - end box unique identifier to which the link is attached
        *@param endPos - end box position from which the link is attached
        *@param x - link x position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param y - link y position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param width - link width in pixels
        *@param height - link height in pixels
        *@return true on success, otherwise false
        */
        void addLinkToView(const QString& type,
                           const QString& uid,
                           const QString& startUID,
                                 int      startPos,
                           const QString& endUID,
                                 int      endPos,
                                 int      x,
                                 int      y,
                                 int      width,
                                 int      height);

        /**
        * Called when a component view should be deleted on the page
        *@param uid - component view unique identifier to delete
        */
        void deleteComponentView(const QString& uid);

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
        * Adds a box view on the page
        *@param type - box type
        *@param uid - box unique identifier
        *@param position - default position where the box will appear
        *@param x - box x position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param y - box y position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param width - link width in pixels
        *@param height - link height in pixels
        *@return true on success, otherwise false
        */
        virtual bool AddBox(const QString&      type,
                            const QString&      uid,
                                  IEBoxPosition position,
                                  int           x,
                                  int           y,
                                  int           width,
                                  int           height);

        /**
        * Adds a link view on the page
        *@param type - link type
        *@param uid - link unique identifier
        *@param startUID - start box unique identifier from which the link is attached
        *@param startPos - start box position from which the link is attached
        *@param endUID - end box unique identifier to which the link is attached
        *@param endPos - end box position from which the link is attached
        *@param x - link x position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param y - link y position in pixels, if position is set to IE_BP_Custom, ignored otherwise
        *@param width - link width in pixels
        *@param height - link height in pixels
        *@return true on success, otherwise false
        */
        virtual bool AddLink(const QString&               type,
                             const QString&               uid,
                             const QString&               startUID,
                                   TSP_QmlBox::IEPosition startPos,
                             const QString&               endUID,
                                   TSP_QmlBox::IEPosition endPos,
                                   int                    x,
                                   int                    y,
                                   int                    width,
                                   int                    height);

        /**
        * Deletes a component view from the page
        *@param uid - page unique identifier to delete
        */
        virtual void DeleteComponent(const QString& uid);

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

        /**
        * Notify that a link was added
        *@param success - if true, the link was added successfully
        */
        virtual Q_INVOKABLE void onLinkAdded(bool success);

        /**
        * Notify that a box should be deleted
        *@param uid - box unique identifier to delete
        */
        virtual Q_INVOKABLE void onDeleteBox(const QString& uid);

        /**
        * Notify that a link should be deleted
        *@param uid - link unique identifier to delete
        */
        virtual Q_INVOKABLE void onDeleteLink(const QString& uid);

    private:
        TSP_Page* m_pPage     = nullptr;
        bool      m_BoxAdded  = false;
        bool      m_LinkAdded = false;
};
