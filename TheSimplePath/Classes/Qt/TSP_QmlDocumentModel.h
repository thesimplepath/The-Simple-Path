/****************************************************************************
 * ==> TSP_QmlDocumentModel ------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document qml model                                      *
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

// std
#include <vector>

// qt
#include <QObject>
#include <QAbstractListModel>

// class prototype
class TSP_QmlDocument;

/**
* Qt document qml model
*@author Jean-Milost Reymond
*/
class TSP_QmlDocumentModel : public QAbstractListModel
{
    Q_OBJECT

    public:
        Q_PROPERTY(int     docStatus        READ getDocStatus        WRITE setDocStatus        NOTIFY docStatusChanged);
        Q_PROPERTY(QString selectedAtlasUID READ getSelectedAtlasUID WRITE setSelectedAtlasUID NOTIFY selectedAtlasUIDChanged);

    public slots:
        /**
        * Gets the document status
        *@return the document status
        */
        int getDocStatus() const;

        /**
        * Sets the document status
        *@param status - the document status
        */
        void setDocStatus(int status);

        /**
        * Gets the selected atlas unique identifier
        *@return the selected atlas unique identifier
        */
        QString getSelectedAtlasUID() const;

        /**
        * Sets the selected atlas unique identifier
        *@param uid - the selected atlas unique identifier
        */
        void setSelectedAtlasUID(QString uid);

    signals:
        /**
        * Called when the document view should be created
        *@param document name - name
        *@param openedCount - opened document count
        */
        void createDocumentView(const QString& name, int openedCount);

        /**
        * Called when the document view should be deleted
        */
        void deleteDocumentView();

        /**
        * Called when an atlas should be added to the document view
        *@param uid - atlas unique identifier
        */
        void addAtlasToView(const QString& uid);

        /**
        * Called when an atlas should be removed from the document view
        *@param uid - atlas unique identifier
        */
        void removeAtlasFromView(const QString& uid);

        /**
        * Called when the selected atlas unique identifier is queried
        */
        void queryAtlasUID();

        /**
        * Called when the document status changed
        *@param status - document status
        */
        void docStatusChanged(int status);

        /**
        * Called when the selected atlas changed
        *@param uid - newly selected atlas unique identifier
        */
        void selectedAtlasUIDChanged(const QString& uid);

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
        *@param pDocument - document which owns this model
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_QmlDocumentModel(TSP_QmlDocument* pDocument, QObject* pParent = nullptr);

        virtual ~TSP_QmlDocumentModel();

        /**
        * Gets the main document
        *@return the main document, nullptr if not found or on error
        */
        virtual TSP_QmlDocument* GetDocument() const;

        /**
        * Creates a new document view on the user interface
        *@return true on success, otherwise false
        */
        virtual bool CreateView();

        /**
        * Deletes the document view on the user interface
        *@return true on success, otherwise false
        */
        virtual bool DeleteView();

        /**
        * Notify that an atlas will be added
        */
        virtual Q_INVOKABLE void beginAddAtlas();

        /**
        * Notify that an atlas was added
        */
        virtual Q_INVOKABLE void endAddAtlas();

        /**
        * Adds an atlas to the view
        *@param uid - atlas unique identifier to add
        */
        virtual Q_INVOKABLE void addAtlas(const QString& uid);

        /**
        * Notify that an atlas will be removed
        */
        virtual Q_INVOKABLE void beginRemoveAtlas();

        /**
        * Notify that an atlas was removed
        */
        virtual Q_INVOKABLE void endRemoveAtlas();

        /**
        * Removes an atlas from the view
        *@param uid - atlas unique identifier to remove
        */
        virtual Q_INVOKABLE void removeAtlas(const QString& uid);

        /**
        * Queries the currently selected atlas unique identifier
        *@return the currently selected atlas unique identifier, empty string if no selection
        */
        virtual QString QuerySelectedAtlasUID();

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
        TSP_QmlDocument* m_pDocument        = nullptr;
        QString          m_SelectedAtlasUID;
};
