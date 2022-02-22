/****************************************************************************
 * ==> TSP_QmlPage ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document page                                           *
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

#include "TSP_QmlPage.h"

 //---------------------------------------------------------------------------
 // TSP_QmlPage
 //---------------------------------------------------------------------------
TSP_QmlPage::TSP_QmlPage(TSP_Item* pOwner) :
    TSP_Page(pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlPage::TSP_QmlPage(const std::wstring& name, TSP_Item* pOwner) :
    TSP_Page(name, pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlPage::~TSP_QmlPage()
{}
//---------------------------------------------------------------------------
TSP_QmlPageProxy* TSP_QmlPage::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void TSP_QmlPage::SetProxy(TSP_QmlPageProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
TSP_Box* TSP_QmlPage::CreateAndAddBox(const std::wstring& name,
                                      const std::wstring& description,
                                      const std::wstring& comments,
                                            int           x,
                                            int           y,
                                            int           width,
                                            int           height)
{
    std::unique_ptr<TSP_QmlBox> pBox = std::make_unique<TSP_QmlBox>(this);

    // add a box on the page view
    if (!CreateBoxView(pBox.get(), "box", x, y, width, height))
        return nullptr;

    // set the box data
    pBox->GetProxy()->setTitle(QString::fromStdWString(name));
    pBox->GetProxy()->setDescription(QString::fromStdWString(description));
    pBox->GetProxy()->setComments(QString::fromStdWString(comments));

    // add newly created box to page
    if (!TSP_Page::Add(pBox.get()))
        return nullptr;

    return pBox.release();
}
//---------------------------------------------------------------------------
TSP_Link* TSP_QmlPage::CreateAndAddLink(const std::wstring&          name,
                                        const std::wstring&          description,
                                        const std::wstring&          comments,
                                        const std::wstring&          startUID,
                                              TSP_QmlBox::IEPosition startPos,
                                        const std::wstring&          endUID,
                                              TSP_QmlBox::IEPosition endPos,
                                              int                    x,
                                              int                    y,
                                              int                    width,
                                              int                    height)
{
    std::unique_ptr<TSP_QmlLink> pLink = std::make_unique<TSP_QmlLink>(this);

    // add a link on the page view
    if (!CreateLinkView(pLink.get(),
                        "link",
                        QString::fromStdWString(startUID),
                        startPos,
                        QString::fromStdWString(endUID),
                        endPos,
                        x,
                        y,
                        width,
                        height))
        return nullptr;

    // set the link data
    pLink->GetProxy()->setTitle(QString::fromStdWString(name));
    pLink->GetProxy()->setDescription(QString::fromStdWString(description));
    pLink->GetProxy()->setComments(QString::fromStdWString(comments));

    // add newly created link to page
    if (!TSP_Page::Add(pLink.get()))
        return nullptr;

    return pLink.release();
}
//---------------------------------------------------------------------------
void TSP_QmlPage::Remove(const std::string& uid)
{
    TSP_Page::Remove(uid);
}
//---------------------------------------------------------------------------
void TSP_QmlPage::Remove(TSP_Component* pComponent)
{
    TSP_Page::Remove(pComponent);
}
//---------------------------------------------------------------------------
