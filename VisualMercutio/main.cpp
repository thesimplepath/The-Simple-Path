/****************************************************************************
 * ==> main ----------------------------------------------------------------*
 ****************************************************************************
 * Description:  The application main entry point                           *
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

// main classes
#include "RPM_GlobalSettings.h"
#include "RPM_Application.h"

// common classes
#include "Common\RPM_StdFileBuffer.h"
#include "Common\RPM_Logger.h"

// qt
#include <QDir>

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    try
    {
        RPM_Logger::IHeader header;
        header.m_Name    = RPM_GlobalSettings::m_AppName;
        header.m_Version = RPM_GlobalSettings::m_AppVersion;

        // open the logger
        RPM_Logger::Instance()->Open(header);
    }
    catch (...)
    {
        return -1;
    }

    int result = 0;

    try
    {
        // configure the Qt attributes
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        // create and run the application
        std::unique_ptr<RPM_Application> pApplication(new RPM_Application(argc, argv));
        result = pApplication->Execute();
    }
    catch (...)
    {
        M_LogException(RPM_ExceptionFormatter::m_GenericTypeName, "Uncaught application exception");
    }

    try
    {
        // close the logger
        RPM_Logger::Instance()->Close();

        QString logDir = "Logs";

        // check if log dir exists, creates one close to the application exe if not
        if (!QDir(logDir).exists())
        {
            QDir().mkdir(logDir);

            // should exists now
            if (!QDir(logDir).exists())
                return -1;
        }

        // build the log file name
        const std::wstring fileName = logDir.toStdWString() + L"\\" + RPM_Logger::Instance()->GetFileName(RPM_GlobalSettings::m_AppName);

        // open a file buffer to write the log
        std::unique_ptr<RPM_StdFileBuffer> pFileBuffer(new RPM_StdFileBuffer());
        pFileBuffer->Open(fileName, RPM_FileBuffer::IEMode::IE_M_Write);

        // write the log to file
        const std::string log = RPM_StringHelper::Utf16ToUtf8(RPM_Logger::Instance()->Get());
        pFileBuffer->Write(log.c_str(), log.length());
    }
    catch (...)
    {
        return -1;
    }

    return result;
}
//---------------------------------------------------------------------------
