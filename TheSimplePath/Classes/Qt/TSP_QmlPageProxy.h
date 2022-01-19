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

/**
* Page proxy
*@author Jean-Milost Reymond
*/
class TSP_QmlPageProxy : public TSP_QmlProxy
{
    Q_OBJECT

    /*REM
    public slots:
        void setParentPage(const QVariant& pPage);
    */

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlPageProxy(QObject* pParent = nullptr);

        virtual ~TSP_QmlPageProxy();

        /**
        * Called when a symbol was added on a page
        *@param pageUID - page unique identifier
        *@param symbolUID - symbol unique identifier
        */
        virtual Q_INVOKABLE void symbolAdded(const QString& pageUID, const QString& symbolUID);

        /**
        * Called when a symbol was added on a page
        *@param pageUID - page unique identifier
        *@param messageUID - message unique identifier
        */
        virtual Q_INVOKABLE void messageAdded(const QString& pageUID, const QString& messageUID);
};
