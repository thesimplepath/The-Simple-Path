import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

// custom qt component
import "Component"

/**
* Atlas view
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_Atlas: this
    property var m_Model: null

    // common properties
    id: ctAtlasView
    objectName: "ctAtlasView"
    anchors.fill: parent

    /**
    * Models stack view
    */
    StackView
    {
        // common properties
        id: svAtlasView
        objectName: "svAtlasView"
        anchors.fill: parent
        initialItem: cpPageItem
    }

    Component
    {
        // common properties
        id: cpPageItem

        TSP_PageView
        {
            // common properties
            id: pvPageView

            // advanced properties
            m_PageWidth:  m_MainFormProxy.getPageWidth()
            m_PageHeight: m_MainFormProxy.getPageHeight()

            /**
            * Adds a start component to the document, with a default size
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            */
            function addStartDefSize(title, description, comments, x, y)
            {
                return addStart(title,
                                description,
                                comments,
                                x,
                                y,
                                m_PageWidth  * 0.18,
                                m_PageHeight * 0.082);
            }

            /**
            * Adds a start component to the document
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            */
            function addStart(title, description, comments, x, y, width, height)
            {
                return addSymbol("start",
                                 title,
                                 description,
                                 comments,
                                 x,
                                 y,
                                 width,
                                 height,
                                 false,
                                 false,
                                 false,
                                 true);
            }

            /**
            * Adds an end component to the document, with a default size
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            */
            function addEndDefSize(title, description, comments, x, y)
            {
                return addEnd(title,
                              description,
                              comments,
                              x,
                              y,
                              m_PageWidth  * 0.18,
                              m_PageHeight * 0.082);
            }

            /**
            * Adds an end component to the document
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            */
            function addEnd(title, description, comments, x, y, width, height)
            {
                return addSymbol("end",
                                 title,
                                 description,
                                 comments,
                                 x,
                                 y,
                                 width,
                                 height,
                                 false,
                                 true,
                                 false,
                                 false);
            }

            /**
            * Adds a process component to the document, with a default size
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            */
            function addProcessDefSize(title, description, comments, x, y)
            {
                return addProcess(title,
                                  description,
                                  comments,
                                  x,
                                  y,
                                  m_PageWidth  * 0.18,
                                  m_PageHeight * 0.082);
            }

            /**
            * Adds a process component to the document
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            */
            function addProcess(title, description, comments, x, y, width, height)
            {
                return addSymbol("process",
                                 title,
                                 description,
                                 comments,
                                 x,
                                 y,
                                 width,
                                 height,
                                 false,
                                 false,
                                 false,
                                 false);
            }

            /**
            * Adds an activity component to the document, with a default size
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            */
            function addActivityDefSize(title, description, comments, x, y)
            {
                return addActivity(title,
                                   description,
                                   comments,
                                   x,
                                   y,
                                   m_PageWidth  * 0.18,
                                   m_PageHeight * 0.082);
            }

            /**
            * Adds an activity component to the document
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            */
            function addActivity(title, description, comments, x, y, width, height)
            {
                return addSymbol("activity",
                                 title,
                                 description,
                                 comments,
                                 x,
                                 y,
                                 width,
                                 height,
                                 true,
                                 true,
                                 true,
                                 true);
            }

            /**
            * Adds a page break component to the document, with a default size
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param isProcess - if true, the page break links to a process instead of a page
            *@param isExit - if true, the page break is an exit instead of an input
            */
            function addPageBreakDefSize(title, description, comments, x, y, isProcess, isExit)
            {
                return addPageBreak(title,
                                    description,
                                    comments,
                                    x,
                                    y,
                                    m_PageWidth  * 0.11,
                                    m_PageHeight * 0.06,
                                    isProcess,
                                    isExit);
            }

            /**
            * Adds a page break component to the document
            *@param title [string] - title
            *@param description [string] - description
            *@param comments [string] - comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            *@param isProcess - if true, the page break links to a process instead of a page
            *@param isExit - if true, the page break is an exit instead of an input
            */
            function addPageBreak(title, description, comments, x, y, width, height, isProcess, isExit)
            {
                let symbol = addSymbol("pageBreak",
                                       title,
                                       description,
                                       comments,
                                       x,
                                       y,
                                       width,
                                       height,
                                       false,
                                       !isProcess && !isExit,
                                       false,
                                       !isProcess && isExit);

                if (!symbol)
                    return null;

                symbol.m_IsProcess = isProcess;
                symbol.m_IsExit    = isExit;

                return symbol;
            }

            /**
            * Adds a symbol component to the document
            *@param title [string] - symbol title
            *@param description [string] - symbol description
            *@param comments [string] - symbol comments
            *@param x [number] - component x position, in pixels
            *@param y [number] - component y position, in pixels
            *@param width [number] - component width, in pixels
            *@param height [number] - component height, in pixels
            */
            function addSymbol(name,
                               title,
                               description,
                               comments,
                               x,
                               y,
                               width,
                               height,
                               leftConnVisible,
                               topConnVisible,
                               rightConnVisible,
                               bottomConnVIsible)
            {
                let componentName;

                // get component name to load
                switch (name)
                {
                    case "start":     componentName = "TSP_Start.qml";     break;
                    case "end":       componentName = "TSP_End.qml";       break;
                    case "procedure": componentName = "TSP_Procedure.qml"; break;
                    case "process":   componentName = "TSP_Process.qml";   break;
                    case "activity":  componentName = "TSP_Activity.qml";  break;
                    case "pageBreak": componentName = "TSP_PageBreak.qml"; break;

                    default:
                    {
                        console.error("Add symbol - unknown component name - " + name);
                        return;
                    }
                }

                // load the component
                let component = Qt.createComponent(componentName);

                // succeeded?
                if (component.status !== Component.Ready)
                {
                    console.error("Add symbol - an error occurred while the component was created - name - " + name +
                                  " - " + component.errorString());
                    return;
                }

                const connectorWidth  = 14;
                const connectorHeight = 14;

                // create and show new item object
                let item = component.createObject(pvPageView.pageContent, {"id":                      "acStart" + m_GenIndex,
                                                                           "objectName":              "acStart" + m_GenIndex,
                                                                           "m_Title":                 title,
                                                                           "m_Description":           description,
                                                                           "m_Comments":              comments,
                                                                           "x":                       x,
                                                                           "y":                       y,
                                                                           "width":                   width,
                                                                           "height":                  height,
                                                                           "m_ScaleFactor":           m_ScaleFactor,
                                                                           "leftConnector.x":        -((connectorWidth  / 2) + 2),
                                                                           "topConnector.y":         -((connectorHeight / 2) + 2),
                                                                           "rightConnector.x":        width  + 2 - (connectorWidth  / 2),
                                                                           "bottomConnector.y":       height + 2 - (connectorHeight / 2),
                                                                           "leftConnector.visible":   leftConnVisible,
                                                                           "topConnector.visible":    topConnVisible,
                                                                           "rightConnector.visible":  rightConnVisible,
                                                                           "bottomConnector.visible": bottomConnVIsible});

                console.log("Add symbol - succeeded - name - " + name + " - id - " + item.objectName);

                ++m_GenIndex;
                return item;
            }

            /**
            * Adds a message component to the document
            *@param title [string] - message title
            *@param description [string] - message description
            *@param comments [string] - message comments
            *@param from [TSP_Connector] - connector belonging to symbol the message is attached from
            *@param to [TSP_Connector] - connector belonging to symbol the message is attached to, if null the message is dragging
            */
            function addMessage(title, description, comments, from, to)
            {
                // load the item component
                let component = Qt.createComponent('TSP_Message.qml');

                // succeeded?
                if (component.status !== Component.Ready)
                {
                    console.error("Add message - an error occurred while the component was created - " + component.errorString());
                    return;
                }

                // create and show new item object
                let item = component.createObject(pvPageView.pageContent, {"id":            "mgMessage" + m_GenIndex,
                                                                           "objectName":    "mgMessage" + m_GenIndex,
                                                                           "m_Title":       title,
                                                                           "m_Description": description,
                                                                           "m_Comments":    comments,
                                                                           "m_From":        from,
                                                                           "m_To":          to,
                                                                           "m_ScaleFactor": m_ScaleFactor,
                                                                           "m_LabelSize.x": m_PageWidth  * 0.17,
                                                                           "m_LabelSize.y": m_PageHeight * 0.067});

                console.log("Add message - succeeded - new item - " + item.objectName);

                ++m_GenIndex;
                return item;
            }

            /**
            * Called when a link should be added
            *@param from [TSP_Connector] - connector belonging to box the link is attached from
            *@param to [TSP_Connector] - connector belonging to box the link is attached to, if null the link is dragging
            *@param linkType [string] - optional link type
            *@return [TSP_Link] added link, null on error
            */
            function doAddLink(from, to, linkType)
            {
                return addMessage("", "", "", from, to);
            }

            /// called when page is loaded
            Component.onCompleted:
            {
                let start = addStartDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200,  50);
                let activity = addActivityDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200, 250);
                let end = addEndDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200, 450);
                let process = addProcessDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "", "", 400, 200);
                let pageBreak = addPageBreakDefSize("Page des cas spéciaux", "", "", 400, 400, false, false);
                let pageBreak2 = addPageBreakDefSize("Page des cas spéciaux", "", "", 550, 400, false, true);
                let pageBreak3 = addPageBreakDefSize("Page des cas spéciaux", "", "", 400, 500, true, false);
                let pageBreak4 = addPageBreakDefSize("Page des cas spéciaux", "", "", 550, 500, true, true);
                addMessage("Demande de tarification exceptionnelle à suivre rapidement", "ID : 5940", "<i>45%</i>", start.bottomConnector, activity.topConnector);
                addMessage("Demande de tarification exceptionnelle à suivre rapidement", "ID : 5940", "<i>45%</i>", activity.bottomConnector, end.topConnector);
            }
        }
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        target: m_Model
    }
}
