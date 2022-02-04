/****************************************************************************
 * ==> TSP_QmlAtlas --------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document atlas                                          *
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

#include "TSP_QmlAtlas.h"

// qt classes
#include "TSP_QmlPage.h"

//---------------------------------------------------------------------------
// TSP_QmlAtlas
//---------------------------------------------------------------------------
TSP_QmlAtlas::TSP_QmlAtlas(TSP_QmlDocument* pOwner) :
    TSP_Atlas(pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlas::TSP_QmlAtlas(const std::wstring& name, TSP_QmlDocument* pOwner) :
    TSP_Atlas(name, pOwner)
{}
//---------------------------------------------------------------------------
TSP_QmlAtlas::~TSP_QmlAtlas()
{}
//---------------------------------------------------------------------------
TSP_QmlAtlasProxy* TSP_QmlAtlas::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::SetProxy(TSP_QmlAtlasProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreatePage()
{
    return new TSP_QmlPage(this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::CreatePage(const std::wstring& name)
{
    return new TSP_QmlPage(name, this);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::AddPage()
{
    return TSP_Atlas::AddPage();
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::AddPage(const std::wstring& name)
{
    return TSP_Atlas::AddPage(name);
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::RemovePage(std::size_t index)
{
    TSP_Atlas::RemovePage(index);
}
//---------------------------------------------------------------------------
void TSP_QmlAtlas::RemovePage(TSP_Page* pPage)
{
    TSP_Atlas::RemovePage(pPage);
}
//---------------------------------------------------------------------------
TSP_Page* TSP_QmlAtlas::GetSelectedPage() const
{
    return nullptr;
}
//---------------------------------------------------------------------------
