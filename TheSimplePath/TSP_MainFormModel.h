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

/**
* Main form model
*@author Jean-Milost Reymond
*/
class TSP_MainFormModel : public QObject
{
    Q_OBJECT

    public:
        /**
        * Document status
        */
        enum class IEDocStatus
        {
            IE_DS_Closed = 0,
            IE_DS_Opened,
            IE_DS_Error
        };
        Q_ENUM(IEDocStatus);

        Q_PROPERTY(int docStatus READ getDocStatus WRITE setDocStatus NOTIFY docStatusChanged);

    Q_SIGNALS:
        void newDocument(const QString& name);
        void docStatusChanged(int status);

    public slots:
        int getDocStatus() const;
        void setDocStatus(int status);

    public:
        /**
        * Constructor
        *@param pParent - parent object owning this object
        */
        TSP_MainFormModel(QObject* pParent = nullptr);

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
        * Called when the new document button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onNewDocumentClicked();

        /**
        * Called when the test button was clicked on the user interface
        */
        virtual Q_INVOKABLE void onTestClicked();

    private:
        IEDocStatus m_DocStatus = IEDocStatus::IE_DS_Closed;
        QPageSize   m_PageSize;
};
