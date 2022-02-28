/****************************************************************************
 * ==> TSP_QmlAtlasPage ----------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document page owned by an atlas                         *
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

#include "TSP_QmlAtlasPage.h"

// qt classes
#include "TSP_QmlProcess.h"

//---------------------------------------------------------------------------
// TSP_QmlAtlasPage
//---------------------------------------------------------------------------
TSP_QmlAtlasPage::TSP_QmlAtlasPage(TSP_QmlAtlas* pOwner) :
    TSP_QmlPage(pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlasPage::TSP_QmlAtlasPage(const std::wstring& name, TSP_QmlAtlas* pOwner) :
    TSP_QmlPage(name, pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlasPage::~TSP_QmlAtlasPage()
{}
//---------------------------------------------------------------------------
TSP_Process* TSP_QmlAtlasPage::CreateAndAddProcess(const std::wstring& name,
                                                   const std::wstring& description,
                                                   const std::wstring& comments,
                                                         int           x,
                                                         int           y,
                                                         int           width,
                                                         int           height)
{
    std::unique_ptr<TSP_QmlProcess> pProcess = std::make_unique<TSP_QmlProcess>(this);

    // add a process on the page view
    if (!CreateBoxView(pProcess.get(), "process", x, y, width, height))
        return nullptr;

    // set the process data
    pProcess->GetProxy()->setTitle(QString::fromStdWString(name));
    pProcess->GetProxy()->setDescription(QString::fromStdWString(description));
    pProcess->GetProxy()->setComments(QString::fromStdWString(comments));

    // add newly created process to page
    if (!TSP_Page::Add(pProcess.get()))
        return nullptr;

    return pProcess.release();
}
//---------------------------------------------------------------------------
