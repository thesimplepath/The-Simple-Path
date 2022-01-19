/****************************************************************************
 * ==> TSP_Component -------------------------------------------------------*
 ****************************************************************************
 * Description:  Component (which may be inserted on a page)                *
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

#include "TSP_Component.h"

//---------------------------------------------------------------------------
// TSP_Component
//---------------------------------------------------------------------------
TSP_Component::TSP_Component(TSP_Page* pOwner) :
    TSP_Item(),
    m_pOwner(pOwner)
{}
//---------------------------------------------------------------------------
TSP_Component::TSP_Component(const std::wstring& title,
                             const std::wstring& description,
                             const std::wstring& comments,
                                   TSP_Page*     pOwner) :
    TSP_Item(),
    m_pOwner(pOwner),
    m_Title(title),
    m_Description(description),
    m_Comments(comments)
{}
//---------------------------------------------------------------------------
TSP_Component::~TSP_Component()
{
    for each (auto pAttribute in m_Attributes)
        delete pAttribute;
}
//---------------------------------------------------------------------------
std::wstring TSP_Component::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
bool TSP_Component::SetTitle(const std::wstring& value)
{
    m_Title = value;
    return true;
}
//---------------------------------------------------------------------------
std::wstring TSP_Component::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
bool TSP_Component::SetDescription(const std::wstring& value)
{
    m_Description = value;
    return true;
}
//---------------------------------------------------------------------------
std::wstring TSP_Component::GetComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
bool TSP_Component::SetComments(const std::wstring& value)
{
    m_Comments = value;
    return true;
}
//---------------------------------------------------------------------------
