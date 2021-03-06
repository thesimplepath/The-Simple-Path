/****************************************************************************
 * ==> TSP_QmlProxy --------------------------------------------------------*
 ****************************************************************************
 * Description:  Proxy between qml view and application engine              *
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

// qt
#include <QObject>

/**
* Proxy between qml view and application engine
*@author Jean-Milost Reymond
*/
class TSP_QmlProxy : public QObject
{
    Q_OBJECT

    public:
        Q_PROPERTY(QString uid READ getUID WRITE setUID NOTIFY uidChanged)

    public slots:
        /**
        * Gets the unique identifier
        *@return the unique identifier
        */
        QString getUID() const;

        /**
        * Sets the unique identifier
        *@param uid - the unique identifier
        */
        void setUID(const QString& uid);

    signals:
        /**
        * Called when the unique identifier changed
        *@param uid - unique identifier
        */
        void uidChanged(const QString& uid);

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlProxy(QObject* pParent = nullptr);

        virtual ~TSP_QmlProxy();

    private:
        std::string m_UID;
};
