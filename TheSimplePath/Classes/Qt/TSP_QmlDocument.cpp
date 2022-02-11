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

#include "TSP_QmlDocument.h"

// std
#include <sstream>

// common classes
#include "Common/TSP_Exception.h"
#include "Common/TSP_GlobalMacros.h"

// qt classes
#include "TSP_QmlAtlas.h"
#include "TSP_QmlProxyDictionary.h"

 // application
#include "TSP_Application.h"

 // qt
#include <QQmlContext>

//---------------------------------------------------------------------------
// TSP_QmlDocument
//---------------------------------------------------------------------------
TSP_QmlDocument::TSP_QmlDocument(TSP_Application* pApp) :
    TSP_Document(),
    m_pApp(pApp)
{
    Initialize();
}
//---------------------------------------------------------------------------
TSP_QmlDocument::TSP_QmlDocument(TSP_Application* pApp, const std::wstring& title) :
    TSP_Document(title),
    m_pApp(pApp)
{
    Initialize();
}
//---------------------------------------------------------------------------
TSP_QmlDocument::~TSP_QmlDocument()
{
    if (m_pDocumentModel)
        delete m_pDocumentModel;
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::DeclareContextProperties(QQmlApplicationEngine* pEngine)
{
    if (!pEngine)
        return;

    pEngine->rootContext()->setContextProperty("tspDocumentModel", m_pDocumentModel);
}
//---------------------------------------------------------------------------
bool TSP_QmlDocument::Create()
{
    M_TRY
    {
        if (!m_pApp)
        {
            M_LogErrorT("Create document - FAILED - application is missing");
            return false;
        }

        if (!m_pDocumentModel)
        {
            M_LogErrorT("Create document - FAILED - document model is missing");
            return false;
        }

        // close the currently opened document before opening a new one
        if (GetStatus() != TSP_Document::IEDocStatus::IE_DS_Closed)
            Close();

        SetStatus(TSP_Document::IEDocStatus::IE_DS_Opening);

        // set the default title
        try
        {
            std::wostringstream sstr;

            //: New document default name
            //% "New document"
            sstr << qtTrId("id-new-document").toStdWString();

            if (m_OpenedCount)
                sstr << L" (" << std::to_wstring(m_OpenedCount) << L")";

            SetTitle(sstr.str());
        }
        catch (...)
        {
            M_LogErrorT("Create document - FAILED - could not set document title");
            return false;
        }

        // create the document view
        if (!m_pDocumentModel->CreateView())
        {
            M_LogErrorT("Create document - FAILED - could not create document view");
            Close();
            return false;
        }

        std::wostringstream sstr;

        //: Root atlas name
        //% "Root-Atlas"
        sstr << qtTrId("id-root-atlas").toStdWString();

        // by default, a document always contain one, and only one, atlas
        TSP_QmlAtlas* pQmlAtlas = static_cast<TSP_QmlAtlas*>(AddAtlas(sstr.str()));

        // was atlas created successfully?
        if (!pQmlAtlas)
        {
            M_LogErrorT("Create document - FAILED - could not create the main atlas");
            Close();
            return false;
        }

        // get the page list model
        TSP_PageListModel* pPageListModel = m_pApp->GetPageListModel();

        // found it?
        if (!pPageListModel)
        {
            M_LogErrorT("Create document - FAILED - could not get the page list model");
            Close();
            return false;
        }

        // set the current page owner
        pPageListModel->SetPageOwner(pQmlAtlas);

        // create a default page
        if (!pPageListModel->addPage())
        {
            M_LogErrorT("Create document - FAILED - could not create the default page");
            Close();
            return false;
        }

        ++m_OpenedCount;

        SetStatus(TSP_Document::IEDocStatus::IE_DS_Opened);

        return true;
    }
    M_CATCH_LOG

    return false;
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::Close()
{
    M_TRY
    {
        if (GetStatus() == TSP_Document::IEDocStatus::IE_DS_Closed)
            return;

        // document model defined?
        if (m_pDocumentModel)
        {
            // delete the document view
            m_pDocumentModel->DeleteView();

            // notify the model that no atlas is selected
            m_pDocumentModel->setSelectedAtlasUID("");
        }

        // main app defined?
        if (m_pApp)
        {
            // get page list model
            TSP_PageListModel* pPageListModel = m_pApp->GetPageListModel();

            // clear the page list model
            if (pPageListModel)
                pPageListModel->clear();
        }

        // close the document itself
        TSP_Document::Close();
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
std::size_t TSP_QmlDocument::GetOpenedCount() const
{
    return m_OpenedCount;
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::CreateAtlas()
{
    return new TSP_QmlAtlas(this);
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::CreateAtlas(const std::wstring& name)
{
    return new TSP_QmlAtlas(name, this);
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::AddAtlas()
{
    M_TRY
    {
        std::wostringstream sstr;

        //: New atlas default name
        //% "New atlas"
        sstr << qtTrId("id-new-atlas").toStdWString();

        const std::size_t atlasCount = GetAtlasCount();

        if (atlasCount)
            sstr << L" (" << std::to_wstring(atlasCount) << L")";

        return AddAtlas(sstr.str());
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::AddAtlas(const std::wstring& name)
{
    M_TRY
    {
        if (!m_pDocumentModel)
        {
            M_LogErrorT("Add atlas - FAILED - document model is missing");
            return nullptr;
        }

        // add a new atlas in document
        TSP_Atlas* pAtlas = TSP_Document::AddAtlas(name);

        // succeeded?
        if (!pAtlas)
        {
            M_LogErrorT("Add atlas - FAILED - atlas could not be created");
            return nullptr;
        }

        // add atlas in the document view
        m_pDocumentModel->beginAddAtlas();
        const bool success = AddAtlasOnDocView(pAtlas);
        m_pDocumentModel->endAddAtlas();

        // succeeded?
        if (!success)
        {
            M_LogErrorT("Add atlas - FAILED - atlas could not be added on view");
            TSP_Document::RemoveAtlas(pAtlas);
            return nullptr;
        }

        return pAtlas;
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::RemoveAtlas(std::size_t index)
{
    M_TRY
    {
        if (!m_pDocumentModel)
        {
            M_LogErrorT("Remove atlas - FAILED - document model is missing");
            return;
        }

        TSP_QmlAtlas* pAtlas = static_cast<TSP_QmlAtlas*>(GetAtlas(index));

        if (!pAtlas)
            return;

        // remove the atlas from the view
        m_pDocumentModel->beginRemoveAtlas();
        m_pDocumentModel->removeAtlas(QString::fromStdString(pAtlas->GetUID()));
        m_pDocumentModel->endRemoveAtlas();

        // remove atlas from the document
        TSP_Document::RemoveAtlas(index);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::RemoveAtlas(TSP_Atlas* pAtlas)
{
    M_TRY
    {
        if (!pAtlas)
            return;

        if (!m_pDocumentModel)
        {
            M_LogErrorT("Remove atlas - FAILED - document model is missing");
            return;
        }

        // remove the atlas from the view
        m_pDocumentModel->beginRemoveAtlas();
        m_pDocumentModel->removeAtlas(QString::fromStdString(pAtlas->GetUID()));
        m_pDocumentModel->endRemoveAtlas();

        // remove atlas from the document
        TSP_Document::RemoveAtlas(pAtlas);
    }
    M_CATCH_LOG
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::GetSelectedAtlas() const
{
    M_TRY
    {
        if (!m_pDocumentModel)
            return nullptr;

        // get the selected atlas unique identifier
        const std::string atlasUID = m_pDocumentModel->QuerySelectedAtlasUID().toStdString();

        // get the atlas
        return TSP_Document::GetAtlas(atlasUID);
    }
    M_CATCH_LOG

    return nullptr;
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::Initialize()
{
    // initialize document model instance
    m_pDocumentModel = new TSP_QmlDocumentModel(this);
}
//---------------------------------------------------------------------------
bool TSP_QmlDocument::AddAtlasOnDocView(TSP_Atlas* pAtlas)
{
    if (!pAtlas)
        return false;

    if (!m_pDocumentModel)
        return false;

    // get atlas unique identifier
    const std::string uid = pAtlas->GetUID();

    // add atlas on the document view
    m_pDocumentModel->addAtlas(QString::fromStdString(uid));

    // get the atlas
    TSP_QmlAtlas* pQmlAtlas = static_cast<TSP_QmlAtlas*>(pAtlas);

    if (!pQmlAtlas)
        return false;

    // get the newly added component proxy
    TSP_QmlAtlasProxy* pProxy = static_cast<TSP_QmlAtlasProxy*>(TSP_QmlProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the atlas and the proxy
    pQmlAtlas->SetProxy(pProxy);
    pProxy->SetAtlas(pQmlAtlas);

    return true;
}
//---------------------------------------------------------------------------
