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
{}
//---------------------------------------------------------------------------
void TSP_QmlDocument::DeclareContextProperties(QQmlApplicationEngine* pEngine)
{
    if (!pEngine)
        return;

    pEngine->rootContext()->setContextProperty("tspDocumentModel", m_pDocumentModel);
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::AddAtlas()
{
    if (!m_pDocumentModel)
        // FIXME LOG
        return nullptr;

    m_pDocumentModel->beginAddAtlas();
    TSP_Document::AddAtlas();
    m_pDocumentModel->endAddAtlas();
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_QmlDocument::AddAtlas(const std::wstring& name)
{
    if (!m_pDocumentModel)
        return nullptr;

    m_pDocumentModel->beginAddAtlas();
    TSP_Document::AddAtlas(name);
    m_pDocumentModel->endAddAtlas();
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::RemoveAtlas(std::size_t index)
{
    if (!m_pDocumentModel)
        return;

    m_pDocumentModel->beginRemoveAtlas();
    TSP_Document::RemoveAtlas(index);
    m_pDocumentModel->endRemoveAtlas();
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::RemoveAtlas(TSP_Atlas* pAtlas)
{
    if (!m_pDocumentModel)
        return;

    m_pDocumentModel->beginRemoveAtlas();
    TSP_Document::RemoveAtlas(pAtlas);
    m_pDocumentModel->endRemoveAtlas();
}
//---------------------------------------------------------------------------
void TSP_QmlDocument::Initialize()
{
    // initialize document instances
    m_pDocumentModel = new TSP_QmlDocumentModel(this);
}
//---------------------------------------------------------------------------
