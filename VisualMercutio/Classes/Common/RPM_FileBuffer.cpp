/****************************************************************************
 * ==> RPM_FileBuffer ------------------------------------------------------*
 ****************************************************************************
 * Description:  Generic file buffer                                        *
 * Contained in: Common                                                     *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - todo FIXME -cFeature -oJean: Set the project name here     *
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

#include "RPM_FileBuffer.h"

//---------------------------------------------------------------------------
// RPM_FileBuffer
//---------------------------------------------------------------------------
RPM_FileBuffer::RPM_FileBuffer() :
    RPM_Buffer(),
    m_Mode(IEMode::IE_M_Unknown)
{}
//---------------------------------------------------------------------------
RPM_FileBuffer::~RPM_FileBuffer()
{}
//---------------------------------------------------------------------------
bool RPM_FileBuffer::Open(const std::string& fileName, IEMode mode)
{
    m_Mode = mode;
    return true;
}
//---------------------------------------------------------------------------
bool RPM_FileBuffer::Open(const std::wstring& fileName, IEMode mode)
{
    m_Mode = mode;
    return true;
}
//---------------------------------------------------------------------------