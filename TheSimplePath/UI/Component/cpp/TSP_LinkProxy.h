/****************************************************************************
 * ==> TSP_LinkProxy -------------------------------------------------------*
 ****************************************************************************
 * Description:  Proxy between a link on the UI and its c++ representation  *
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

#pragma once

 // component classes
#include "TSP_ComponentProxy.h"

// qt
#include <QObject>

/**
* Link proxy
*@author Jean-Milost Reymond
*/
class TSP_LinkProxy : public TSP_ComponentProxy
{
    Q_OBJECT

    // properties
    Q_PROPERTY(QString title       READ getTitle       WRITE setTitle       NOTIFY titleChanged)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString comments    READ getComments    WRITE setComments    NOTIFY commentsChanged)

    public slots:
        /**
        * Gets the box title
        *@return the box title
        */
        virtual QString getTitle() const;

        /**
        * Gets the box description
        *@return the box description
        */
        virtual QString getDescription() const;

        /**
        * Gets the box comments
        *@return the box comments
        */
        virtual QString getComments() const;

        /**
        * Sets the box title
        *@param title - the box title
        */
        virtual void setTitle(const QString& title);

        /**
        * Sets the box description
        *@return the box description
        */
        virtual void setDescription(const QString& description);

        /**
        * Sets the box comments
        *@return the box comments
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
        explicit TSP_LinkProxy(QObject* pParent = nullptr);

        virtual ~TSP_LinkProxy();

    private:
        QString m_Title;
        QString m_Description;
        QString m_Comments;
};
