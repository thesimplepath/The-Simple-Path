/****************************************************************************
 * ==> TSP_Activity --------------------------------------------------------*
 ****************************************************************************
 * Description:  Activity component                                         *
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

#include "TSP_Activity.h"

//---------------------------------------------------------------------------
// TSP_Activity
//---------------------------------------------------------------------------
TSP_Activity::TSP_Activity(TSP_Page* pOwner) :
    TSP_Box(pOwner)
{}
//---------------------------------------------------------------------------
TSP_Activity::TSP_Activity(const std::wstring& title,
                           const std::wstring& description,
                           const std::wstring& comments,
                                 TSP_Page*     pOwner) :
    TSP_Box(title, description, comments, pOwner)
{}
//---------------------------------------------------------------------------
TSP_Activity::~TSP_Activity()
{}
//---------------------------------------------------------------------------
