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
TSP_Document::~TSP_Document()
{
    for each (auto pModel in m_Models)
        delete pModel;
}
//---------------------------------------------------------------------------
TSP_Model* TSP_Document::AddModel()
{
    auto pModel = std::make_unique<TSP_Model>();
    m_Models.push_back(pModel.get());
    return pModel.release();
}
//---------------------------------------------------------------------------
TSP_Model* TSP_Document::AddModel(const std::wstring& name)
{
    auto pModel = std::make_unique<TSP_Model>(name);
    m_Models.push_back(pModel.get());
    return pModel.release();
}
//---------------------------------------------------------------------------
void TSP_Document::RemoveModel(std::size_t index)
{
    // is index out of bounds?
    if (index >= m_Models.size())
        return;

    // delete the model
    delete m_Models[index];
    m_Models.erase(m_Models.begin() + index);
}
//---------------------------------------------------------------------------
void TSP_Document::RemoveModel(TSP_Model* pModel)
{
    // search for model to remove
    for (std::size_t i = 0; i < m_Models.size(); ++i)
        // found it?
        if (m_Models[i] == pModel)
        {
            // remove the model and exit
            RemoveModel(i);
            return;
        }
}
//---------------------------------------------------------------------------
TSP_Model* TSP_Document::GetModel(std::size_t index) const
{
    if (index >= m_Models.size())
        return nullptr;

    return m_Models[index];
}
//---------------------------------------------------------------------------
std::size_t TSP_Document::GetModelCount() const
{
    return m_Models.size();
}
//---------------------------------------------------------------------------
bool TSP_Document::Load(const std::wstring fileName)
{
    M_LogT("Load document - " << fileName);

    //m_Title

    /*
    for each (auto pModel in m_Models)
        pModel->Load();
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
    for each (auto pModel in m_Models)
        pModel->Save();
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
