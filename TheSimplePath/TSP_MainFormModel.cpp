/****************************************************************************
 * ==> TSP_MainFormModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  Main form model                                            *
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

#include "TSP_MainFormModel.h"

// component classes
#include "UI\Component\cpp\TSP_ProxyDictionary.h"

// qt
#include <QSize>

// windows
#include <windows.h>

//---------------------------------------------------------------------------
// TSP_MainFormModel
//---------------------------------------------------------------------------
TSP_MainFormModel::TSP_MainFormModel(QObject* pParent) :
    QObject(pParent)
{}
//---------------------------------------------------------------------------
TSP_MainFormModel::~TSP_MainFormModel()
{}
//---------------------------------------------------------------------------
int TSP_MainFormModel::getDocStatus() const
{
    return (int)m_DocStatus;
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::setDocStatus(int docStatus)
{
    m_DocStatus = (IEDocStatus)docStatus;
}
//---------------------------------------------------------------------------
int TSP_MainFormModel::getPageWidth() const
{
    int width = 0;
    HDC hDC   = ::GetDC(nullptr);

    try
    {
        const float ppx   = ::GetDeviceCaps(hDC, LOGPIXELSX);
                    width = std::ceilf(m_PageSize.size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point).width() * (ppx / 72.0f));
    }
    catch (...)
    {}

    if (hDC)
        ::ReleaseDC(nullptr, hDC);

    return width;
}
//---------------------------------------------------------------------------
int TSP_MainFormModel::getPageHeight() const
{
    int height = 0;
    HDC hDC    = ::GetDC(nullptr);

    try
    {
        const float ppx    = ::GetDeviceCaps(hDC, LOGPIXELSY);
                    height = std::ceilf(m_PageSize.size(QPageSize::PageSizeId::A4, QPageSize::Unit::Point).height() * (ppx / 72.0f));
    }
    catch (...)
    {}

    if (hDC)
        ::ReleaseDC(nullptr, hDC);

    return height;
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onNewDocumentClicked()
{
    emit newDocument("MyDoc");

    if (m_DocStatus != IEDocStatus::IE_DS_Opened)
    {}

    int test2 = 0;
}
//---------------------------------------------------------------------------
void TSP_MainFormModel::onTestClicked()
{
    //REM TSP_ProxyDictionary::Instance()->test();
}
//---------------------------------------------------------------------------
