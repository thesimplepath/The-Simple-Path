/****************************************************************************
 * ==> TSP_Application -----------------------------------------------------*
 ****************************************************************************
 * Description: The main application class                                  *
 * Developer:   Jean-Milost Reymond                                         *
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

#include "TSP_Application.h"

// common classes
#include "Common\TSP_Logger.h"

// qt classes
#include "QT\TSP_QmlBoxProxy.h"
#include "QT\TSP_QmlLinkProxy.h"
#include "QT\TSP_QmlPageProxy.h"
#include "QT\TSP_QmlAtlasProxy.h"

// qt
#include <QQmlContext>

#ifndef _DEBUG
    #define REDIRECT_QML_LOGS_TO_LOGGER
#endif

//---------------------------------------------------------------------------
// TSP_Application
//---------------------------------------------------------------------------
TSP_Application::TSP_Application(int argc, char* argv[], const std::wstring& url) :
    m_URL(url)
{
    InitializeQt(argc, argv);
}
//---------------------------------------------------------------------------
TSP_Application::~TSP_Application()
{
    // disconnect qml logger
    qInstallMessageHandler(nullptr);

    // engine should be deleted first, as it contains the qml interface with
    // all its associated signals
    if (m_pEngine)
        delete m_pEngine;

    if (m_pDocument)
        delete m_pDocument;

    if (m_pPageListModel)
        delete m_pPageListModel;

    if (m_pMainFormModel)
        delete m_pMainFormModel;

    if (m_pApp)
        delete m_pApp;
}
//---------------------------------------------------------------------------
void TSP_Application::DeclareContextProperties()
{
    M_LogT("Execute - declaring context properties...");

    // component proxies registration
    qmlRegisterType<TSP_QmlBoxProxy>  ("thesimplepath.proxys", 1, 0, "BoxProxy");
    qmlRegisterType<TSP_QmlLinkProxy> ("thesimplepath.proxys", 1, 0, "LinkProxy");
    qmlRegisterType<TSP_QmlPageProxy> ("thesimplepath.proxys", 1, 0, "PageProxy");
    qmlRegisterType<TSP_QmlAtlasProxy>("thesimplepath.proxys", 1, 0, "AtlasProxy");

    // models registration
    m_pEngine->rootContext()->setContextProperty("tspMainFormModel", m_pMainFormModel);
    m_pEngine->rootContext()->setContextProperty("tspPageListModel", m_pPageListModel);

    // declare document context properties
    m_pDocument->DeclareContextProperties(m_pEngine);

    M_LogT("Execute - context properties declared");
}
//---------------------------------------------------------------------------
QGuiApplication* TSP_Application::GetQtApp() const
{
    return m_pApp;
}
//---------------------------------------------------------------------------
QQmlApplicationEngine* TSP_Application::GetQtEngine() const
{
    return m_pEngine;
}
//---------------------------------------------------------------------------
TSP_QmlDocument* TSP_Application::GetDocument() const
{
    return m_pDocument;
}
//---------------------------------------------------------------------------
TSP_MainFormModel* TSP_Application::GetMainFormModel() const
{
    return m_pMainFormModel;
}
//---------------------------------------------------------------------------
TSP_PageListModel* TSP_Application::GetPageListModel() const
{
    return m_pPageListModel;
}
//---------------------------------------------------------------------------
int TSP_Application::Execute()
{
    M_LogT("Execute - initialization started...");

    DeclareContextProperties();

    const QUrl url(QStringLiteral("qrc:/") + QString::fromStdWString(m_URL));

    // listen to onAppCreated signal
    (void)QObject::connect(m_pEngine,
                           &QQmlApplicationEngine::objectCreated,
                           m_pApp,
                           [url](QObject* pObj, const QUrl& objUrl)
                           {
                               if (!pObj && url == objUrl)
                                   QCoreApplication::exit(-1);
                           },
                           Qt::QueuedConnection);

    m_pEngine->load(url);

    M_LogT("Execute - initialization terminated successfully - now application starts");

    return m_pApp->exec();
}
//---------------------------------------------------------------------------
void TSP_Application::InitializeQt(int argc, char* argv[])
{
    // configure the Qt attributes
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // redirect QT log messages to application logger
    #ifdef REDIRECT_QML_LOGS_TO_LOGGER
        qInstallMessageHandler(RedirectQmlLogs);
    #endif

    // initialize application instances
    m_pApp           = new QGuiApplication(argc, argv);
    m_pEngine        = new QQmlApplicationEngine();
    m_pMainFormModel = new TSP_MainFormModel(this);
    m_pPageListModel = new TSP_PageListModel(this);
    m_pDocument      = new TSP_QmlDocument(this);
}
//---------------------------------------------------------------------------
void TSP_Application::RedirectQmlLogs(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    const std::wstring message = msg.toStdWString();
    const std::string  file(context.file     ? context.file     : "");
    const std::string  func(context.function ? context.function : "");

    // redirect qml log to application log
    switch (type)
    {
        case QtDebugMsg:
        case QtInfoMsg:     M_LogT     ("Qml - " << message << " - " << file << ":" << context.line << ", " << func); break;
        case QtWarningMsg:  M_LogWarnT ("Qml - " << message << " - " << file << ":" << context.line << ", " << func); break;
        case QtCriticalMsg:
        case QtFatalMsg:    M_LogErrorT("Qml - " << message << " - " << file << ":" << context.line << ", " << func); break;
        default:            M_LogT     ("Qml - " << message << " - " << file << ":" << context.line << ", " << func); break;
    }
}
//---------------------------------------------------------------------------
