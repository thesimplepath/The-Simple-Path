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
#include "TSP_Atlas.h"
#include "TSP_Page.h"

/**
* The main resource and process manager document
*@author Jean-Milost Reymond
*/
class TSP_Document
{
    public:
        /**
        * Document status
        *@note This enum is linked with the one located in TSP_DocumentView.
        *      Don't modify it without updating its twin
        */
        enum class IEDocStatus
        {
            IE_DS_Closed = 0,
            IE_DS_Opening,
            IE_DS_Opened,
            IE_DS_Error
        };

        TSP_Document();

        /**
        * Constructor
        *@param title - the document title
        */
        TSP_Document(const std::wstring& title);

        virtual ~TSP_Document();

        /**
        * Creates a new document
        *@return true on success, otherwise false
        */
        virtual bool Create() = 0;

        /**
        * Closes a document
        */
        virtual void Close();

        /**
        * Gets the document status
        *@return the document status
        */
        virtual inline IEDocStatus GetStatus() const;

        /**
        * Sets the document status
        *@param status - the document status
        */
        virtual inline void SetStatus(IEDocStatus status);

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
        * Creates an atlas
        *@return newly created atlas
        */
        virtual TSP_Atlas* CreateAtlas();

        /**
        * Creates an atlas
        *@param name - atlas name
        *@return newly created atlas
        */
        virtual TSP_Atlas* CreateAtlas(const std::wstring& name);

        /**
        * Adds a new atlas in document
        *@return newly added atlas
        */
        virtual TSP_Atlas* AddAtlas();

        /**
        * Adds a new atlas in document
        *@param name - atlas name
        *@return newly added atlas
        */
        virtual TSP_Atlas* AddAtlas(const std::wstring& name);

        /**
        * Removes an atlas
        *@param index - atlas index to remove
        */
        virtual void RemoveAtlas(std::size_t index);

        /**
        * Removes an atlas
        *@param pAtlas - atlas to remove
        */
        virtual void RemoveAtlas(TSP_Atlas* pAtlas);

        /**
        * Gets atlas at index
        *@param index - atlas index to get
        *@return atlas, nullptr if not found or on error
        */
        virtual TSP_Atlas* GetAtlas(std::size_t index) const;

        /**
        * Gets atlas matching with uid
        *@param uid - atlas unique identifier to get
        *@return atlas, nullptr if not found or on error
        */
        virtual TSP_Atlas* GetAtlas(const std::string& uid) const;

        /**
        * Gets atlas count
        *@return atlas count
        */
        virtual std::size_t GetAtlasCount() const;

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
        typedef std::vector<TSP_Atlas*> IAtlases;

        IAtlases     m_Atlases;
        std::wstring m_Title;
        IEDocStatus  m_DocStatus = IEDocStatus::IE_DS_Closed;
};

//---------------------------------------------------------------------------
// TSP_Document
//---------------------------------------------------------------------------
TSP_Document::IEDocStatus TSP_Document::GetStatus() const
{
    return m_DocStatus;
}
//---------------------------------------------------------------------------
void TSP_Document::SetStatus(IEDocStatus status)
{
    m_DocStatus = status;
}
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
