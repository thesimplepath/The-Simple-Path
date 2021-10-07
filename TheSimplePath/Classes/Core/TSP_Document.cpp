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

// rapid json
#include "rapidjson/document.h"

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
    std::unique_ptr<TSP_Model> pModel(new TSP_Model());
    m_Models.push_back(pModel.get());
    return pModel.release();
}
//---------------------------------------------------------------------------
TSP_Model* TSP_Document::AddModel(const std::wstring& name)
{
    std::unique_ptr<TSP_Model> pModel(new TSP_Model(name));
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
    //m_NbrGen;
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
    std::unique_ptr<rapidjson::Document> pJsonDoc(new rapidjson::Document());

    //m_NbrGen;
    //m_Title

    /*
    for each (auto pModel in m_Models)
        pModel->Save();
    */

    return true;
}
//---------------------------------------------------------------------------
