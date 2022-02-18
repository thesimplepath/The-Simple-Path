/****************************************************************************
 * ==> TSP_QmlDocument -----------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document                                                *
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

// core classes
#include "Core\TSP_Document.h"

// qt classes
#include "TSP_QmlDocumentModel.h"

// qt
#include <QQmlApplicationEngine>

// class prototype
class TSP_Application;

/**
* Qt document
*@author Jean-Milost Reymond
*/
class TSP_QmlDocument : public TSP_Document
{
    public:
        /**
        * Constructor
        *@param pApp - main application
        */
        TSP_QmlDocument(TSP_Application* pApp);

        /**
        * Constructor
        *@param pApp - main application
        *@param title - the document title
        */
        TSP_QmlDocument(TSP_Application* pApp, const std::wstring& title);

        virtual ~TSP_QmlDocument();

        /**
        * Declares the context properties (i.e models linked with qml, ...)
        *@param pEngine - application engine
        */
        virtual void DeclareContextProperties(QQmlApplicationEngine* pEngine);

        /**
        * Creates a new document
        *@return true on success, otherwise false
        */
        virtual bool Create();

        /**
        * Closes a document
        */
        virtual void Close();

        /**
        * Gets the opened count
        *@return the opened count
        */
        virtual std::size_t GetOpenedCount() const;

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
        * Creates a new atlas and adds it in document
        *@return newly created atlas
        */
        virtual TSP_Atlas* CreateAndAddAtlas();

        /**
        * Creates a new atlas and adds it in document
        *@param name - atlas name
        *@return newly created atlas
        */
        virtual TSP_Atlas* CreateAndAddAtlas(const std::wstring& name);

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
        * Gets the currently selected atlas
        *@return the currently selected atlas, nullptr if no atlas selected or on error
        */
        virtual TSP_Atlas* GetSelectedAtlas() const;

    private:
        TSP_Application*      m_pApp           = nullptr;
        TSP_QmlDocumentModel* m_pDocumentModel = nullptr;
        std::size_t           m_OpenedCount    = 0;

        /**
        * Initializes the qt application
        */
        void Initialize();

        /**
        * Creates a new atlas view and adds it to the user interface
        *@param pPage - page for which the view should be added
        */
        bool CreateAtlasView(TSP_Atlas* pAtlas);
};
