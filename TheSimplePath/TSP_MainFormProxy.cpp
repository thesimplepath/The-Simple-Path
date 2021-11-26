/****************************************************************************
 * ==> TSP_MainFormProxy ---------------------------------------------------*
 ****************************************************************************
 * Description:  The main form proxy between c++ application and qml        *
 *               interface                                                  *
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

#include "TSP_MainFormProxy.h"

// qt
#include <QSize>

// windows
#include <windows.h>

//---------------------------------------------------------------------------
// TSP_MainFormProxy
//---------------------------------------------------------------------------
TSP_MainFormProxy::TSP_MainFormProxy(QObject* pParent) :
    QObject(pParent)
{}
//---------------------------------------------------------------------------
TSP_MainFormProxy::~TSP_MainFormProxy()
{}
//---------------------------------------------------------------------------
int TSP_MainFormProxy::getPageWidth() const
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
int TSP_MainFormProxy::getPageHeight() const
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
void TSP_MainFormProxy::onAddActivityClicked()
{
}
//---------------------------------------------------------------------------
