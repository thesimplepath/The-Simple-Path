/****************************************************************************
 * ==> TSP_DocumentModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  A model for the document                                   *
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
#include "Core\TSP_Document.h"

// model classes
#include "Models\TSP_AtlasModel.h"

// qt
#include <QObject>
#include <QAbstractListModel>

/**
* A model for the document
*@author Jean-Milost Reymond
*/
class TSP_DocumentModel : public QAbstractListModel
{
    Q_OBJECT
    //Q_PROPERTY(float x READ userName WRITE setUserName NOTIFY userNameChanged)

    public:
        /**
        * Data roles
        */
        enum class IEDataRole
        {
            IE_DR_Title = 0,
            IE_DR_ModelName
        };

        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit TSP_DocumentModel(QObject* pParent = nullptr);

        virtual ~TSP_DocumentModel();

        /**
        * Gets the main document
        *@return the main document, nullptr if not found or on error
        */
        virtual TSP_Document* GetDocument() const;

        /**
        * Gets the atlas model
        *@return the atlas model, nullptr if not found or on error
        */
        virtual TSP_AtlasModel* GetAtlasModel() const;

        /**
        * Adds an atlas
        *@param name - atlas name
        */
        virtual Q_INVOKABLE void addAtlas(const QString& name);

        /**
        * Removes an atlas
        *@param index - atlas index to remove
        */
        virtual Q_INVOKABLE void removeAtlas(std::size_t index);

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
        TSP_Document*   m_pDocument   = nullptr;
        TSP_AtlasModel* m_pAtlasModel = nullptr;
};
