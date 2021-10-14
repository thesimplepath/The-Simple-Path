/****************************************************************************
 * ==> TSP_Exception -------------------------------------------------------*
 * **************************************************************************
 * Description : Provides a class to throw an exception, and to format and  *
 *               log exceptions                                             *
 * Contained in: Common                                                     *
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

#include "TSP_Exception.h"

// std
#include <sstream>

//---------------------------------------------------------------------------
// TSP_ExceptionFormatter
//---------------------------------------------------------------------------
const std::string TSP_ExceptionFormatter::m_GenericTypeName = "Generic";
//---------------------------------------------------------------------------
std::string TSP_ExceptionFormatter::Format(const std::string& type,
                                           const std::string& message,
                                           const std::string& file,
                                           const std::string& function,
                                                 std::size_t  line)
{
    std::ostringstream sstr;

    sstr << "[";

    if (type.empty())
        sstr << "Unknown";
    else
        sstr << type;

    sstr << " exception raised]" << std::endl << "[Message]  ";

    if (message.empty())
        sstr << "Unknown exception" << std::endl;
    else
        sstr << message << std::endl;

    sstr << "[File] "     << file     << std::endl
         << "[Function] " << function << std::endl
         << "[Line] "     << line     << std::endl;

    return sstr.str();
}
//---------------------------------------------------------------------------
std::string TSP_ExceptionFormatter::Format_HTML(const std::string& type,
                                                const std::string& message,
                                                const std::string& file,
                                                const std::string& function,
                                                      std::size_t  line)
{
    std::ostringstream sstr;

    sstr << "[";

    if (type.empty())
        sstr << "Unknown";
    else
        sstr << type;

    sstr << " exception raised]" << "<br>" << "[Message]  ";

    if (message.empty())
        sstr << "Unknown exception" << "<br>";
    else
        sstr << message << "<br>";

    sstr << "[File] "     << file     << "<br>"
         << "[Function] " << function << "<br>"
         << "[Line] "     << line     << "<br>";

    return sstr.str();
}
//---------------------------------------------------------------------------
std::string TSP_ExceptionFormatter::Message(const std::string& message,
                                            const std::string& function,
                                                  std::size_t  line)
{
    std::ostringstream sstr;

    if (message.empty())
        sstr << "Unknown exception";
    else
        sstr << message;

    sstr << std::endl;

    sstr << "[Function] " << function << std::endl
         << "[Line] "     << line     << std::endl;

    return sstr.str();
}
//---------------------------------------------------------------------------
std::string TSP_ExceptionFormatter::Message_HTML(const std::string& message,
                                                 const std::string& function,
                                                       std::size_t  line)
{
    std::ostringstream sstr;

    if (message.empty())
        sstr << "Unknown exception";
    else
        sstr << message;

    sstr << "<br>";

    sstr << "[Function] " << function << "<br>"
         << "[Line] "     << line     << "<br>";

    return sstr.str();
}
//---------------------------------------------------------------------------
// TSP_Exception
//---------------------------------------------------------------------------
TSP_Exception::TSP_Exception() throw()
{}
//---------------------------------------------------------------------------
TSP_Exception::TSP_Exception(const std::string& message,
                             const std::string& file,
                             const std::string& function,
                                   std::size_t  line) throw()
{
    m_Message  = message;
    m_File     = file;
    m_Function = function;
    m_Line     = line;
}
//---------------------------------------------------------------------------
TSP_Exception::~TSP_Exception() throw()
{}
//---------------------------------------------------------------------------
const char* TSP_Exception::what() const throw()
{
    return Format();
}
//---------------------------------------------------------------------------
const char* TSP_Exception::Format() const
{
    std::ostringstream sstr;

    sstr << "[TSP_Exception raised]" << std::endl << "[Message]  ";

    if (m_Message.empty())
        sstr << "Unknown exception" << std::endl;
    else
        sstr << m_Message << std::endl;

    sstr << "[File] "     << m_File     << std::endl
         << "[Function] " << m_Function << std::endl
         << "[Line] "     << m_Line     << std::endl;

    return sstr.str().c_str();
}
//---------------------------------------------------------------------------
std::string TSP_Exception::Format_HTML() const
{
    std::ostringstream sstr;

    sstr << "[TSP_Exception raised]" << "<br>" << "[Message]  ";

    if (m_Message.empty())
        sstr << "Unknown exception" << "<br>";
    else
        sstr << m_Message << "<br>";

    sstr << "[File] "     << m_File     << "<br>"
         << "[Function] " << m_Function << "<br>"
         << "[Line] "     << m_Line     << "<br>";

    return sstr.str().c_str();
}
//---------------------------------------------------------------------------
const std::string& TSP_Exception::Message() const
{
    return m_Message;
}
//---------------------------------------------------------------------------
