/****************************************************************************
 * ==> TSP_QmlLinkProxy ----------------------------------------------------*
 ****************************************************************************
 * Description:  Link proxy between qml view and application engine         *
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

 // component classes
#include "TSP_QmlProxy.h"

// qt
#include <QObject>

// class prototypes
class TSP_Link;

/**
* Link proxy
*@author Jean-Milost Reymond
*/
class TSP_QmlLinkProxy : public TSP_QmlProxy
{
    Q_OBJECT

    public:
        Q_PROPERTY(QString title       READ getTitle       WRITE setTitle       NOTIFY titleChanged)
        Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
        Q_PROPERTY(QString comments    READ getComments    WRITE setComments    NOTIFY commentsChanged)

    public slots:
        /**
        * Gets the link title
        *@return the link title
        */
        virtual QString getTitle() const;

        /**
        * Gets the link description
        *@return the link description
        */
        virtual QString getDescription() const;

        /**
        * Gets the link comments
        *@return the link comments
        */
        virtual QString getComments() const;

        /**
        * Sets the link title
        *@param title - the link title
        */
        virtual void setTitle(const QString& title);

        /**
        * Sets the link description
        *@return the link description
        */
        virtual void setDescription(const QString& description);

        /**
        * Sets the link comments
        *@return the link comments
        */
        virtual void setComments(const QString& comments);

    signals:
        void titleChanged(const QString& title);
        void descriptionChanged(const QString& description);
        void commentsChanged(const QString& comments);

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlLinkProxy(QObject* pParent = nullptr);

        virtual ~TSP_QmlLinkProxy();

        /**
        * Gets the linked link component
        *@return the linked link component, nullptr if no link
        */
        virtual TSP_Link* GetLink() const;

        /**
        * Sets the linked link component
        *@param pLink - the linked link component
        */
        virtual void SetLink(TSP_Link* pLink);

    private:
        TSP_Link* m_pLink = nullptr;
};
