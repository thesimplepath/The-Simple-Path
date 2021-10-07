/****************************************************************************
 * ==> TSP_Document --------------------------------------------------------*
 ****************************************************************************
 * Description:  The main resource and process manager document             *
 * Contained in: Core                                                       *
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
#include "TSP_Model.h"
#include "TSP_Page.h"
#include "TSP_Element.h"

/**
* The main resource and process manager document
*@author Jean-Milost Reymond
*/
class TSP_Document
{
    public:
        TSP_Document();
        virtual ~TSP_Document();

        /**
        * Gets the document title
        *@return the document title
        */
        virtual inline std::wstring GetTitle() const;

        /**
        * Sets the model title
        *@param title - the document title
        */
        virtual inline void SetTitle(const std::wstring& title);

        /**
        * Adds a new model in document
        *@return newly added model
        */
        virtual TSP_Model* AddModel();

        /**
        * Adds a new model in document
        *@param name - model name
        *@return newly added model
        */
        virtual TSP_Model* AddModel(const std::wstring& name);

        /**
        * Removes a business model
        *@param index - business model index to remove
        */
        virtual void RemoveModel(std::size_t index);

        /**
        * Removes a business model
        *@param index - business model index to remove
        */
        virtual void RemoveModel(TSP_Model* pModel);

        /**
        * Gets model at index
        *@param index - model index to get
        *@return model, nullptr if not found or on error
        */
        virtual TSP_Model* GetModel(std::size_t index) const;

        /**
        * Gets model count
        *@return model count
        */
        virtual std::size_t GetModelCount() const;

        /**
        * Loads a document from a file
        *@param fileName - document file name
        *@return true on success, otherwise false
        */
        // todo FIXME -cFeature -oJean: select a data type, see: https://doc.qt.io/qt-5/topics-data-storage.html
        virtual bool Load(const std::wstring fileName);

        /**
        * Saves a document to a file
        *@param fileName - document file name
        *@return true on success, otherwise false
        */
        // todo FIXME -cFeature -oJean: select a data type, see: https://doc.qt.io/qt-5/topics-data-storage.html
        virtual bool Save(const std::wstring fileName) const;

    private:
        typedef std::vector<TSP_Model*> IModels;

        IModels      m_Models;
        std::wstring m_Title;
};

//---------------------------------------------------------------------------
// TSP_Document
//---------------------------------------------------------------------------
std::wstring TSP_Document::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
void TSP_Document::SetTitle(const std::wstring& title)
{
    m_Title = title;
}
//---------------------------------------------------------------------------
