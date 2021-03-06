/****************************************************************************
 * ==> TSP_Application -----------------------------------------------------*
 ****************************************************************************
 * Description:  The main application class                                 *
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
#include <string>

// qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>

// qt classes
#include "Qt\TSP_QmlDocument.h"

// application
#include "TSP_MainFormModel.h"
#include "TSP_PageListModel.h"

/**
* Main application
*@author Jean-Milost Reymond
*/
class TSP_Application
{
    public:
        /**
        * Constructor
        *@param argc - argument count contained in argv
        *@param argv - argument vector passed by the user
        *@param iconID - application icon identifier in resources
        *@param url - qml resources url to load
        */
        TSP_Application(int argc, char* argv[], int iconID, const std::wstring& url);

        virtual ~TSP_Application();

        /**
        * Declares the context properties (i.e models linked with qml, ...)
        */
        void DeclareContextProperties();

        /**
        * Gets the Qt application
        *@return the Qt application, nullptr if not found or on error
        */
        virtual QGuiApplication* GetQtApp() const;

        /**
        * Gets the Qt application engine
        *@return the Qt application engine, nullptr if not found or on error
        */
        virtual QQmlApplicationEngine* GetQtEngine() const;

        /**
        * Gets the document
        *@return the document
        */
        virtual TSP_QmlDocument* GetDocument() const;

        /**
        * Gets the main form model
        *@return the main form model
        */
        virtual TSP_MainFormModel* GetMainFormModel() const;

        /**
        * Gets the page list model
        *@return the page list model
        */
        virtual TSP_PageListModel* GetPageListModel() const;

        /**
        * Executes the main application
        *@return success or error code
        */
        virtual int Execute();

    private:
        QGuiApplication*       m_pApp           = nullptr;
        QQmlApplicationEngine* m_pEngine        = nullptr;
        TSP_QmlDocument*       m_pDocument      = nullptr;
        TSP_MainFormModel*     m_pMainFormModel = nullptr;
        TSP_PageListModel*     m_pPageListModel = nullptr;
        std::wstring           m_URL;
        int                    m_IconID         = 0;

        /**
        * Initializes the qt application
        *@param argc - argument count contained in argv
        *@param argv - argument vector passed by the user
        */
        void InitializeQt(int argc, char* argv[]);

        /**
        * Redirects qml logs to application logger
        */
        static void RedirectQmlLogs(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};
