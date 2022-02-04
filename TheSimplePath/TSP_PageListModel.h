/****************************************************************************
 * ==> TSP_PageListModel ---------------------------------------------------*
 ****************************************************************************
 * Description: Page list model                                             *
 * Developer:   Jean-Milost Reymond                                         *
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
#include <QAbstractListModel>

// class prototype
class TSP_Application;

/**
* Page list model
*@author Jean-Milost Reymond
*/
class TSP_PageListModel : public QAbstractListModel
{
    Q_OBJECT

    /*REM
    public:
        Q_PROPERTY(QString itemName READ getItemName WRITE setItemName NOTIFY itemNameChanged);
        Q_PROPERTY(QString selectedAtlasUID READ getSelectedAtlasUID WRITE setSelectedAtlasUID NOTIFY selectedAtlasUIDChanged);
    */

    //REM
    //public slots:
    //    /**
    //    * Gets the document status
    //    *@return the document status
    //    */
    //    int getDocStatus() const;

    //    /**
    //    * Sets the document status
    //    *@param status - the document status
    //    */
    //    void setDocStatus(int status);

    //    /**
    //    * Gets the selected atlas unique identifier
    //    *@return the selected atlas unique identifier
    //    */
    //    QString getSelectedAtlasUID() const;

    //    /**
    //    * Sets the selected atlas unique identifier
    //    *@param uid - the selected atlas unique identifier
    //    */
    //    void setSelectedAtlasUID(QString uid);

    //signals:
    //    void createDocumentView(const QString& name, int openedCount);
    //    void deleteDocumentView();
    //    void addAtlasToView(const QString& uid);
    //    void removeAtlasFromView(const QString& uid);
    //    void queryAtlasUID();
    //    void docStatusChanged(int status);
    //    void selectedAtlasUIDChanged(const QString& uid);

    signals:
        void testSignal();

    public:
        /**
        * Data roles
        */
        enum class IEDataRole
        {
            IE_DR_Title = 0
        };

        /**
        * Constructor
        *@param pApp - main application
        *@param pParent - parent object owning this object
        */
        explicit TSP_PageListModel(TSP_Application* pApp, QObject* pParent = nullptr);

        virtual ~TSP_PageListModel();

        /**
        * Called when the add page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onAddPageClicked();

        /**
        * Called when the delete page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onDeletePageClicked();

        /**
        * Adds a page
        */
        virtual Q_INVOKABLE void addPage();

        /**
        * Gets the page name at index
        */
        virtual Q_INVOKABLE QString getPageName(int index) const;

        /**
        * Get row count
        *@param parent - the parent row index from which the count should be performed
        *@return the row count
        */
        virtual Q_INVOKABLE int rowCount(const QModelIndex& pParent = QModelIndex()) const;

        /**
        * Get data at row index
        *@param index - row index
        *@param role - data role
        *@return the data, empty value if not found or on error
        */
        virtual Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const;

        /**
        * Get role names
        *@return the role names
        */
        virtual QHash<int, QByteArray> roleNames() const;

    private:
        TSP_Application* m_pApp = nullptr;
        std::size_t      m_TempCount = 0;
};
