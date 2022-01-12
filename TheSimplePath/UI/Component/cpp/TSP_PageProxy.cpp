/****************************************************************************
 * ==> TSP_PageProxy -------------------------------------------------------*
 ****************************************************************************
 * Description:  Proxy between a page on the UI and its c++ representation  *
 * Contained in: Component                                                  *
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

#include "TSP_PageProxy.h"

//---------------------------------------------------------------------------
// TSP_PageProxy
//---------------------------------------------------------------------------
TSP_PageProxy::TSP_PageProxy(QObject* pParent) :
    TSP_ComponentProxy(pParent)
{}
//---------------------------------------------------------------------------
TSP_PageProxy::~TSP_PageProxy()
{}
//---------------------------------------------------------------------------
void TSP_PageProxy::symbolAdded(const QString& pageUID, const QString& symbolUID)
{
    int ii = 0;
}
//---------------------------------------------------------------------------
void TSP_PageProxy::messageAdded(const QString& pageUID, const QString& messageUID)
{
    int ii = 0;
}
//---------------------------------------------------------------------------
