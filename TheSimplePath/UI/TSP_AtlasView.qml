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
        id: cpPageItem

        TSP_PageView
        {
            // property int m_GenIndex: 0

            id: pvPageView

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
                return addSymbol("start", title, description, comments, x, y, width, height, false, false, false, true);
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
                return addSymbol("end", title, description, comments, x, y, width, height, false, true, false, false);
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
                return addSymbol("process", title, description, comments, x, y, width, height, false, false, false, false);
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
                return addSymbol("activity", title, description, comments, x, y, width, height, true, true, true, true);
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
            */
            function addPageBreak(title, description, comments, x, y, width, height)
            {
                return addSymbol("pageBreak", title, description, comments, x, y, width, height, false, false, false, false);
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
            function addSymbol(name, title, description, comments, x, y, width, height, leftConnVisible, topConnVisible, rightConnVisible, bottomConnVIsible)
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

                let connectorWidth  = 14;
                let connectorHeight = 14;

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
            *@param from [TSP_Connector] - connector belonging to symbol the message is attached from
            *@param to [TSP_Connector] - connector belonging to symbol the message is attached to, if null the message is dragging
            */
            function addMessage(title, from, to)
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
                let item = component.createObject(pvPageView.pageContent, {"id":         "mgMessage" + m_GenIndex,
                                                                           "objectName": "mgMessage" + m_GenIndex,
                                                                           "m_Title":    title,
                                                                           "m_From":     from,
                                                                           "m_To":       to});

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
                return addMessage(from, to);
            }

            /// called when page is loaded
            Component.onCompleted:
            {
                let start = addStart("<b>Start</b>", "ID: 1234", "Team: Alpha", 200,  50,  100, 80);
                let activity = addActivity("<b>Activity</b>", "ID: 5678", "Team: Bravo", 200, 250, 100, 80);
                let end = addEnd("<b>End</b>", "ID: 9012", "Team: Zulu", 200, 450, 100, 80);
                let process = addProcess("<b>Process</b>", "", "", 400, 200, 100, 80);
                let pageBreak = addPageBreak("<b>Page break</b>", "", "", 400, 400, 100, 80);
                addMessage("Message 1", start.bottomConnector, activity.topConnector);
                addMessage("Message 2", activity.bottomConnector, end.topConnector);
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
