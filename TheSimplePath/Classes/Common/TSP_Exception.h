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

#pragma once

// std
#include <exception>
#include <string>

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_THROW_EXCEPTION(message)             throw TSP_Exception                       (message, __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_EXCEPTION(type, message)      TSP_ExceptionFormatter::Format      (type, message, __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_EXCEPTION_HTML(type, message) TSP_ExceptionFormatter::Format_HTML (type, message, __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_MESSAGE(message)              TSP_ExceptionFormatter::Message           (message,           __FUNCTION__, __LINE__)
#define M_FORMAT_MESSAGE_HTML(message)         TSP_ExceptionFormatter::Message_HTML      (message,           __FUNCTION__, __LINE__)
#define M_ASSERT(condition)\
{\
    if (!(condition))\
        M_THROW_EXCEPTION(std::string("Assertion failed - ") + #condition);\
}
//---------------------------------------------------------------------------

/**
* Exception formatter
*@author Jean-Milost Reymond
*/
class TSP_ExceptionFormatter
{
    public:
        const static std::string m_GenericTypeName;

        /**
        * Formats exception message for logs
        *@param type - type of exception (STD, TSP_Exception, ...)
        *@param message - message to format
        *@param file - the name of the file where the exception was raised
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the exception was raised
        *@return formatted message
        */
        static std::string Format(const std::string& type,
                                  const std::string& message,
                                  const std::string& file,
                                  const std::string& function,
                                        std::size_t  line);

        /**
        * Formats exception message for HTML logs
        *@param type - type of exception (STD, TSP_Exception, ...)
        *@param message - message to format
        *@param file - the name of the file where the exception was raised
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the exception was raised
        *@return formatted message
        */
        static std::string Format_HTML(const std::string& type,
                                       const std::string& message,
                                       const std::string& file,
                                       const std::string& function,
                                             std::size_t  line);

        /**
        * Formats a message to display to user
        *@param message - message to format
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the exception was raised
        *@return formatted message
        */
        static std::string Message(const std::string& message,
                                   const std::string& function,
                                         std::size_t  line);

        /**
        * Formats a message to display to user for HTML
        *@param message - message to format
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the exception was raised
        *@return formatted message
        */
        static std::string Message_HTML(const std::string& message,
                                        const std::string& function,
                                              std::size_t  line);
};

/**
* Exception class
*@note This class is cross-platform
*@author Jean-Milost Reymond
*/
class TSP_Exception : public std::exception
{
    public:
        /**
        * Constructor
        */
        TSP_Exception() throw();

        /**
        * Constructor
        *@param message - exception message
        */
        TSP_Exception(const std::string& message,
                      const std::string& file,
                      const std::string& function,
                            std::size_t  line) throw();

        /**
        * Destructor
        */
        virtual ~TSP_Exception() throw();

        /**
        * Gets default exception error message
        *@return default exception error message
        */
        virtual const char* what() const throw();

        /**
        * Formats exception text
        *@return formatted text
        */
        virtual const char* Format() const;

        /**
        * Formats exception text for HTML
        *@return formatted text
        */
        virtual std::string Format_HTML() const;

        /**
        * Gets exception message
        *@return exception message
        */
        virtual const std::string& Message() const;

    private:
        std::string m_FormattedMessage;
        std::string m_Message;
        std::string m_File;
        std::string m_Function;
        std::size_t m_Line = 0;
};
