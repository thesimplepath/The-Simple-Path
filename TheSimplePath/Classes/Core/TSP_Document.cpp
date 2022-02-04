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

#include "TSP_Document.h"

 // common classes
#include "Common/TSP_StringHelper.h"
#include "Common/TSP_FileHelper.h"
#include "Common/TSP_JsonHelper.h"
#include "Common/TSP_StdFileBuffer.h"
#include "Common/TSP_Logger.h"

//---------------------------------------------------------------------------
// TSP_Document
//---------------------------------------------------------------------------
TSP_Document::TSP_Document()
{}
//---------------------------------------------------------------------------
TSP_Document::TSP_Document(const std::wstring& title) :
    m_Title(title)
{}
//---------------------------------------------------------------------------
TSP_Document::~TSP_Document()
{
    for each (auto pAtlas in m_Atlases)
        delete pAtlas;
}
//---------------------------------------------------------------------------
void TSP_Document::Close()
{
    // already closed?
    if (GetStatus() == TSP_Document::IEDocStatus::IE_DS_Closed)
        return;

    // delete atlases
    for each (auto pAtlas in m_Atlases)
        delete pAtlas;

    m_Atlases.clear();

    // reset values to default
    m_Title.clear();
    m_DocStatus = TSP_Document::IEDocStatus::IE_DS_Closed;
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::CreateAtlas()
{
    return new TSP_Atlas(this);
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::CreateAtlas(const std::wstring& name)
{
    return new TSP_Atlas(name, this);
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::AddAtlas()
{
    std::unique_ptr<TSP_Atlas> pAtlas(CreateAtlas());
    m_Atlases.push_back(pAtlas.get());
    return pAtlas.release();
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::AddAtlas(const std::wstring& name)
{
    std::unique_ptr<TSP_Atlas> pAtlas(CreateAtlas(name));
    m_Atlases.push_back(pAtlas.get());
    return pAtlas.release();
}
//---------------------------------------------------------------------------
void TSP_Document::RemoveAtlas(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Atlases.size())
        return;

    // delete the atlas
    delete m_Atlases[index];
    m_Atlases.erase(m_Atlases.begin() + index);
}
//---------------------------------------------------------------------------
void TSP_Document::RemoveAtlas(TSP_Atlas* pAtlas)
{
    // search for atlas to remove
    for (std::size_t i = 0; i < m_Atlases.size(); ++i)
        // found it?
        if (m_Atlases[i] == pAtlas)
        {
            // remove the atlas and exit
            RemoveAtlas(i);
            return;
        }
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::GetAtlas(std::size_t index) const
{
    if (index >= m_Atlases.size())
        return nullptr;

    return m_Atlases[index];
}
//---------------------------------------------------------------------------
TSP_Atlas* TSP_Document::GetAtlas(const std::string& uid) const
{
    // search for atlas matching with the uid
    for (IAtlases::const_iterator it = m_Atlases.begin(); it != m_Atlases.end(); ++it)
        // found it?
        if ((*it)->GetUID() == uid)
            return (*it);

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t TSP_Document::GetAtlasCount() const
{
    return m_Atlases.size();
}
//---------------------------------------------------------------------------
bool TSP_Document::Load(const std::wstring fileName)
{
    M_LogT("Load document - " << fileName);

    //m_Title

    /*
    for each (auto pAtlas in m_Atlases)
        pAtlas->Load();
    */

    return true;
}
//---------------------------------------------------------------------------
bool TSP_Document::Save(const std::wstring fileName) const
{
    M_LogT("Save document - " << fileName);

    if (TSP_FileHelper::FileExists(fileName))
    {
        // todo FIXME -cFeature -oJean: ask Qt to show a popup to overwrite the file and fail if user rejects the overwrite
    }

    // create a json document
    auto pJsonDoc = std::make_unique<TSP_JsonHelper::IDocumentW>();
    pJsonDoc->SetObject();

    // create document title value
    TSP_JsonHelper::IValueW title;
    title.SetString(TSP_JsonHelper::IStringRefW(m_Title.c_str()));

    // set document title
    pJsonDoc->AddMember(L"title", title, pJsonDoc->GetAllocator());

    /*REM
    TSP_JsonHelper::IValueW documentValue(rapidjson::kObjectType);
    documentValue.AddMember(L"title2", TSP_JsonHelper::IStringRefW(L"m_Title2"), pJsonDoc->GetAllocator());

    pJsonDoc->AddMember(L"document", documentValue, pJsonDoc->GetAllocator());
    */

    /*
    for each (auto pAtlas in m_Atlases)
        pAtlas->Save();
    */

    TSP_JsonHelper::IStringBufferW       stringBuffer;
    TSP_JsonHelper::IStringBufferWriterW stringBufferWriter(stringBuffer);
    pJsonDoc->Accept(stringBufferWriter);

    const wchar_t* pOutput = stringBuffer.GetString();

    /*REM
    std::ofstream ofs("output.json");
    rapidjson::OStreamWrapper osw(ofs);

    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    pJsonDoc->Accept(writer);
    */

    /*
    // write the json content to the file
    auto pFileBuffer = std::make_unique<TSP_StdFileBuffer>;
    pFileBuffer->Open(fileName, TSP_FileBuffer::IEMode::IE_M_Write);
    pFileBuffer->Write(buffer.GetString(), buffer.GetSize());
    */

    return true;
}
//---------------------------------------------------------------------------
