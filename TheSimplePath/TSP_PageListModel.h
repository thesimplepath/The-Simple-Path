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

    signals:
        void showSelectedPage(int index);

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
        * Called when the add page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onAddPageClicked();

        /**
        * Called when the delete page button was clicked on the page list view
        */
        virtual Q_INVOKABLE void onDeletePageClicked();

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
        * Gets the page name at index
        */
        virtual Q_INVOKABLE QString getPageName(int index) const;

        /**
        * Get page at index
        *@return page, nullptr if not found or on error
        */
        virtual TSP_Page* GetPage(int index) const;

        /**
        * Get currently selected page
        *@return selected page, nullptr if not found or on error
        */
        virtual TSP_Page* GetSelectedPage() const;

        /**
        * Get currently selected page index
        *@return selected index, or -1 if no page selected
        */
        virtual Q_INVOKABLE int getSelectedPageIndex() const;

        /**
        * Called when a new page was selected from user interface
        *@param index - selected page index, -1 if no page selected
        */
        virtual Q_INVOKABLE void onPageSelected(int index);

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
        TSP_Application* m_pApp             =  nullptr;
        TSP_Item*        m_pPageOwner       =  nullptr;
        int              m_SelectedPageItem = -1;
};
