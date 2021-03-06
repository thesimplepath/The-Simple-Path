/****************************************************************************
 * ==> main ----------------------------------------------------------------*
 ****************************************************************************
 * Description:  The application main entry point                           *
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

// main classes
#include "TSP_GlobalSettings.h"
#include "TSP_Application.h"

// common classes
#include "Common\TSP_StdFileBuffer.h"
#include "Common\TSP_Logger.h"

// qt classes
#ifdef _DEBUG
    #include "Qt/TSP_QmlProxyDictionary.h"
#endif

// application
#include "resource.h"

// qt
#include <QDir>

// windows
#include <objbase.h>

// uncomment the line below to log the memory leaks
#ifdef _DEBUG
    //#define LOG_MEMORY_LEAKS
#endif

// todo FIXME -cFeature -oJean: To generate a documentation from the source code, see: https://doc.qt.io/qt-5/01-qdoc-manual.html

//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // initialize memory leaks detection structures
    #ifdef LOG_MEMORY_LEAKS
        if (!SUCCEEDED(::CoInitialize(nullptr)))
            return -1;

        _CrtMemState sOld;
        _CrtMemState sNew;
        _CrtMemState sDiff;

        // take a memory snapshot before execution begins
        ::_CrtMemCheckpoint(&sOld);
    #endif

    try
    {
        TSP_Logger::IHeader header;
        header.m_Name    = TSP_GlobalSettings::m_AppName;
        header.m_Version = TSP_GlobalSettings::m_AppVersion;

        // open the logger
        TSP_Logger::Instance()->Open(header);
    }
    catch (...)
    {
        return -1;
    }

    int result = 0;

    try
    {
        // create and run the application
        auto pApplication = std::make_unique<TSP_Application>(argc, argv, IDI_SIMPLE_PATH_ICON, L"UI/TSP_Main.qml");
             result       = pApplication->Execute();
    }
    catch (...)
    {
        M_LogException(TSP_ExceptionFormatter::m_GenericTypeName, "Uncaught application exception");
    }

    try
    {
        // close the logger
        TSP_Logger::Instance()->Close();

        QString logDir = "Logs";

        // check if log dir exists, creates one close to the application executable file if not
        if (!QDir(logDir).exists())
        {
            QDir().mkdir(logDir);

            // should exists now
            if (!QDir(logDir).exists())
                return -1;
        }

        // build the log file name
        const std::wstring fileName = logDir.toStdWString() + L"\\" + TSP_Logger::Instance()->GetFileName(TSP_GlobalSettings::m_AppName);

        // open a file buffer to write the log
        auto pFileBuffer = std::make_unique<TSP_StdFileBuffer>();
        pFileBuffer->Open(fileName, TSP_FileBuffer::IEMode::IE_M_Write);

        // write the log to file
        const std::string log = TSP_StringHelper::Utf16ToUtf8(TSP_Logger::Instance()->Get());
        pFileBuffer->Write(log.c_str(), log.length());
    }
    catch (...)
    {
        return -1;
    }

    // detect memory leaks, log them if found
    #ifdef LOG_MEMORY_LEAKS
        TSP_Logger::Release();
        TSP_QmlProxyDictionary::Release();

        // take a memory snapshot after execution ends
        ::_CrtMemCheckpoint(&sNew);

        // found a difference between memories?
        if (::_CrtMemDifference(&sDiff, &sOld, &sNew))
        {
            ::OutputDebugString(L"-----------_CrtMemDumpStatistics ---------\n");
            ::_CrtMemDumpStatistics(&sDiff);
            ::OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------\n");
            ::_CrtMemDumpAllObjectsSince(&sOld);
            ::OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------\n");
            ::_CrtDumpMemoryLeaks();
        }

        ::CoUninitialize();
    #endif

    return result;
}
//---------------------------------------------------------------------------
