/****************************************************************************
 * ==> TSP_MainFormModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  Main form model                                            *
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
#include <QObject>
#include <QPageSize>

// class prototypes
class TSP_Application;
class TSP_QmlDocument;
class TSP_QmlAtlas;
class TSP_QmlPage;

/**
* Main form model
*@author Jean-Milost Reymond
*/
class TSP_MainFormModel : public QObject
{
    Q_OBJECT

    signals:
        /**
        * Called when an error should be shown to the user
        *@param title - error title
        *@param msg - error message
        *@param detailedMsg - error detailed message
        */
        void showErrorDialog(const QString& title, const QString& msg, const QString& detailedMsg);

    public:
        /**
        * Constructor
        *@param pApp - main application
        *@param pParent - parent object owning this object
        */
        explicit TSP_MainFormModel(TSP_Application* pApp, QObject* pParent = nullptr);

        virtual ~TSP_MainFormModel();

        /**
        * Gets page width, in pixels
        *@return page width, in pixels
        */
        virtual Q_INVOKABLE int getPageWidth() const;

        /**
        * Gets page height, in pixels
        *@return page height, in pixels
        */
        virtual Q_INVOKABLE int getPageHeight() const;

        /**
        * Shows an error dialog box to the user
        *@param title - dialog title
        *@param msg - error message
        *@param detailedMsg - detailed error message, ignored if empty
        */
        virtual Q_INVOKABLE void showError(const QString& title, const QString& msg, const QString& detailedMsg = "");

        /**
        * Called when the new document button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onNewDocumentClicked();

        /**
        * Called when the close document button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onCloseDocumentClicked();

        /**
        * Called when the add process button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onAddBoxClicked();

        /**
        * Called when the add process button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onAddProcessClicked();

    private:
        TSP_Application* m_pApp      = nullptr;
        QPageSize        m_PageSize;

        /**
        * Get document
        *@return document, nullptr if not found or on error
        */
        TSP_QmlDocument* GetDocument() const;

        /**
        * Get selected atlas
        *@return selected atlas, nullptr if no selection or on error
        */
        TSP_QmlAtlas* GetSelectedAtlas() const;

        /**
        * Get selected page
        *@return selected page, nullptr if no selection or on error
        */
        TSP_QmlPage* GetSelectedPage() const;
};
