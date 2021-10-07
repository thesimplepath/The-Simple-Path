/****************************************************************************
 * ==> TSP_ProcedureSymbolModel --------------------------------------------*
 ****************************************************************************
 * Description:  A model for the procedure symbol                           *
 * Contained in: Models                                                     *
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
#include <vector>

// core classes
#include "Core\TSP_ProcedureSymbol.h"

// qt
#include <QObject>

/**
* A model for the procedure symbol
*@author Jean-Milost Reymond
*/
class TSP_ProcedureSymbolModel : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(float x READ userName WRITE setUserName NOTIFY userNameChanged)

    public:
        TSP_ProcedureSymbolModel(QObject* pParent = nullptr);

        virtual ~TSP_ProcedureSymbolModel();

    private:
        float m_X      = 0.0f;
        float m_Y      = 0.0f;
        float m_Width  = 100.0f;
        float m_Height = 80.0f;

        // act on qml property directly
        //object->setProperty("width", 500);
        //QQmlProperty(object, "width").write(500);
        //https://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html
        //https://doc.qt.io/qt-5/qtqml-cppintegration-topic.html
};
