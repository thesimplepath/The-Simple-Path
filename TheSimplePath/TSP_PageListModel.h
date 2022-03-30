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

// core classes
#include "Core/TSP_Item.h"
#include "Core/TSP_Page.h"

// qt
#include <QObject>
#include <QAbstractListModel>

// class prototype
class TSP_Application;
class TSP_QmlDocument;

/**
* Page list model
*@author Jean-Milost Reymond
*/
class TSP_PageListModel : public QAbstractListModel
{
    Q_OBJECT

    signals:
        /**
        * Called when the selected page should be shown
        *@param index - page index
        *@param uid - page unique identifier
        */
        void showSelectedPage(int index, const QString& uid);

    public:
        /**
        * Data roles
        */
        enum class IEDataRole
        {
            IE_DR_PageName = 0
        };

        /**
        * Constructor
        *@param pApp - main application
        *@param pParent - parent object owning this object
        */
        explicit TSP_PageListModel(TSP_Application* pApp, QObject* pParent = nullptr);

        virtual ~TSP_PageListModel();

        /**
        * Gets the current page owner
        *@return the current page owner, nullptr if no current page owner defined
        */
        virtual TSP_Item* GetPageOwner() const;

        /**
        * Sets the current page owner
        *@param pPageOwner - the current page owner
        */
        virtual void SetPageOwner(TSP_Item* pPageOwner);

        /**
        * Queries the page owner unique identifier
        *@return the page owner unique identifier, empty string if no page owner defined
        */
        virtual Q_INVOKABLE QString queryPageOwnerUID() const;

        /**
        * Called when the add page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onAddPageClicked();

        /**
        * Called when the delete page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onDeletePageClicked();

        /**
        * Called when a process is double-clicked
        *@param uid - process unique identifier
        */
        virtual Q_INVOKABLE void onProcessDblClicked(const QString& uid);

        /**
        * Clears the view content
        */
        virtual Q_INVOKABLE void clear();

        /**
        * Adds a page
        *@return true on success, otherwise false
        */
        virtual Q_INVOKABLE bool addPage();

        /**
        * Deletes a page
        *@return true on success, otherwise false
        */
        virtual Q_INVOKABLE bool deletePage();

        /**
        * Gets page at index
        *@return page, nullptr if not found or on error
        */
        virtual TSP_Page* GetPage(int index) const;

        /**
        * Gets the page name at index
        *@param index - page index for which the name should be get
        *@return the page name, empty string if not found or on error
        */
        virtual Q_INVOKABLE QString getPageName(int index) const;

        /**
        * Gets currently selected page
        *@return selected page, nullptr if not found or on error
        */
        virtual TSP_Page* GetSelectedPage() const;

        /**
        * Gets the selected page unique identifier
        *@return the selected page unique identifier, empty string if no selection or on error
        */
        virtual QString GetSelectedPageUID() const;

        /**
        * Gets currently selected page index
        *@return selected index, or -1 if no page selected
        */
        virtual Q_INVOKABLE int getSelectedPageIndex() const;

        /**
        * Called when a new page was selected from user interface
        *@param index - selected page index, -1 if no page selected
        */
        virtual Q_INVOKABLE void onPageSelected(int index);

        /**
        * Gets row count
        *@param parent - the parent row index from which the count should be performed
        *@return the row count
        */
        virtual Q_INVOKABLE int rowCount(const QModelIndex& pParent = QModelIndex()) const;

        /**
        * Gets data at row index
        *@param index - row index
        *@param role - data role
        *@return the data, empty value if not found or on error
        */
        virtual Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const;

        /**
        * Gets role names
        *@return the role names
        */
        virtual QHash<int, QByteArray> roleNames() const;

    private:
        TSP_Application* m_pApp             =  nullptr;
        TSP_Item*        m_pPageOwner       =  nullptr;
        int              m_SelectedPageItem = -1;

        /**
        * Gets document
        *@return document, nullptr if not found or on error
        */
        TSP_QmlDocument* GetDocument() const;

        /**
        * Shows an error message to user
        *@param title - error title
        *@param msg - error message
        */
        void ShowError(const QString& title, const QString& msg);
};
