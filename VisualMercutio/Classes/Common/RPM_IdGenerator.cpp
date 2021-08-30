/****************************************************************************
 * ==> RPM_IdGenerator -----------------------------------------------------*
 ****************************************************************************
 * Description:  Identifier generator                                       *
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

#include "RPM_IdGenerator.h"

// std
#include <stdexcept>

//---------------------------------------------------------------------------
RPM_IdGenerator* RPM_IdGenerator::m_pIdGen = nullptr;
std::mutex       RPM_IdGenerator::m_Mutex;
//---------------------------------------------------------------------------
RPM_IdGenerator::RPM_IdGenerator()
{}
//---------------------------------------------------------------------------
RPM_IdGenerator::RPM_IdGenerator(const RPM_IdGenerator& other)
{
    new std::runtime_error("Cannot create a copy of a singleton class");
}
//---------------------------------------------------------------------------
RPM_IdGenerator::~RPM_IdGenerator()
{}
//---------------------------------------------------------------------------
const RPM_IdGenerator& RPM_IdGenerator::operator = (const RPM_IdGenerator& other)
{
    new std::runtime_error("Cannot create a copy of a singleton class");

    // useless and never reached, but otherwise VS generates an error
    return *this;
}
//---------------------------------------------------------------------------
RPM_IdGenerator* RPM_IdGenerator::Instance()
{
    // check instance out of the thread lock (double check lock)
    if (!m_pIdGen)
    {
        // lock up the thread
        std::unique_lock<std::mutex> lock(m_Mutex);

        // create the instance
        if (!m_pIdGen)
            m_pIdGen = new (std::nothrow)RPM_IdGenerator();
    }

    // still not created?
    if (!m_pIdGen)
        throw new std::runtime_error("Could not create the Identifier Generator unique instance");

    return m_pIdGen;
}
//---------------------------------------------------------------------------
std::size_t RPM_IdGenerator::GetNextID() const
{
    ++const_cast<std::size_t&>(m_CurId);

    return m_CurId - 1;
}
//---------------------------------------------------------------------------
