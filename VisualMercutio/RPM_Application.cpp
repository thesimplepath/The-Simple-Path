/****************************************************************************
 * ==> RPM_Application -----------------------------------------------------*
 ****************************************************************************
 * Description:  The main application class                                 *
 * Contained in: Core                                                       *
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

#include "RPM_Application.h"

//---------------------------------------------------------------------------
RPM_Application::RPM_Application(int argc, char* argv[]) :
    m_pApp(new QGuiApplication(argc, argv)),
    m_pEngine(new QQmlApplicationEngine()),
    m_pDocument(new RPM_Document())
{}
//---------------------------------------------------------------------------
RPM_Application::~RPM_Application()
{
    if (m_pApp)
        delete m_pApp;

    if (m_pEngine)
        delete m_pEngine;

    if (m_pDocument)
        delete m_pDocument;
}
//---------------------------------------------------------------------------
QGuiApplication* RPM_Application::GetQtApp() const
{
    return m_pApp;
}
//---------------------------------------------------------------------------
QQmlApplicationEngine* RPM_Application::GetQtEngine() const
{
    return m_pEngine;
}
//---------------------------------------------------------------------------
RPM_Document* RPM_Application::GetDocument() const
{
    return m_pDocument;
}
//---------------------------------------------------------------------------
int RPM_Application::Execute()
{
    const QUrl url(QStringLiteral("qrc:/UI/main.qml"));

    QObject::connect(m_pEngine,
                     &QQmlApplicationEngine::objectCreated,
                     m_pApp,
                     [url](QObject* pObj, const QUrl& objUrl)
                     {
                         if (!pObj && url == objUrl)
                             QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);

    m_pEngine->load(url);

    return m_pApp->exec();
}
//---------------------------------------------------------------------------
