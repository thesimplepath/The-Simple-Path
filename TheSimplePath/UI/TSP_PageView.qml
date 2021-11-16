import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

// javascript
import "TSP_JSHelper.js" as JSHelper

/**
* Page view
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_Page:  this
    property var m_Model: null

    // common properties
    id:           ctPageView
    objectName:   "ctPageView"
    anchors.fill: parent

    /**
    * Page viewport
    */
    Rectangle
    {
        // common properties
        id: rcPage
        objectName: "rcPage"
        anchors.fill: parent
        clip: true

        /**
        * Page mouse area
        */
        MouseArea
        {
            // advanced properties
            property var  m_Target:  parent
            property int  m_PrevX:   0
            property int  m_PrevY:   0
            property bool m_Panning: false

            // common properties
            id: maPage
            objectName: "maPage"
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: rcPageContent.m_DraggingMsg ? Qt.CrossCursor : (m_Panning ? Qt.ClosedHandCursor : Qt.OpenHandCursor);

            /// called when mouse is pressed above page
            onPressed: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.forceActiveFocus(true);

                m_PrevX   = mouseEvent.x;
                m_PrevY   = mouseEvent.y;
                m_Panning = true;
            }

            /// called when mouse is released after been pressed above page
            onReleased: function(mouseEvent)
            {
                m_Panning = false;
            }

            /// called when mouse position changed above page
            onPositionChanged: function(mouseEvent)
            {
                // do nothing if mouse button is not pressed
                if (!pressed)
                    return;

                // calculate next horizontal scroll position, and apply it
                let deltaX    = (m_PrevX - mouseEvent.x) / rcPageContent.width;
                hbar.position = JSHelper.clamp(hbar.position + deltaX, 0.0, 1.0 - (hbar.size));

                // calculate next vertical scroll position, and apply it
                let deltaY    = (m_PrevY - mouseEvent.y) / rcPageContent.height;
                vbar.position = JSHelper.clamp(vbar.position + deltaY, 0.0, 1.0 - (vbar.size));

                m_PrevX = mouseEvent.x;
                m_PrevY = mouseEvent.y;
            }

            /// called when mouse wheel was rolled above page
            onWheel: function(mouseWheel)
            {
                let offset    = mouseWheel.angleDelta.y * 0.0001;
                vbar.position = Math.min(Math.max(vbar.position - offset, 0.0), 1.0 - (vbar.size));

                mouseWheel.accepted = true;
            }
        }

        /**
        * Page content
        */
        Rectangle
        {
            // advanced properties
            property bool m_DraggingMsg: false

            // common properties
            id: rcPageContent
            objectName: "rcPageContent"
            color: "white"
            x: -hbar.position * width
            y: -vbar.position * height
            width: 2480
            height: 3508

            /**
            * Page background
            */
            Canvas
            {
                // common properties
                id: cvPageBackground
                anchors.fill: parent

                /// called when canvas is painted
                onPaint:
                {
                    // get drawing context
                    let context = getContext("2d");

                    // fill page content
                    context.fillStyle = "transparent";
                    context.fillRect(0, 0, width, height);

                    let pointSize = 2;
                    let step      = 20;

                    // configure line properties
                    context.lineWidth   = 1;
                    context.strokeStyle = "grey";
                    context.setLineDash([pointSize, step - pointSize]);

                    // iterate through lines to draw
                    for (let i = 1; i < height / step; ++i)
                    {
                        // draw a line of points
                        context.beginPath();
                        context.moveTo(0,         (i * step));
                        context.lineTo(width - 1, (i * step));
                        context.stroke();
                    }
                }
            }

            /*REM*/
            TSP_Box
            {
                id: symbol1
                objectName: "symbol1"
                x: 50
                y: 50
                width: 100
                height: 80

                //nameLabel.text: "1"
            }

            TSP_Box
            {
                id: symbol2
                objectName: "symbol2"
                x: 200
                y: 400
                width: 100
                height: 80

                //nameLabel.text: "2"
            }

            TSP_Box
            {
                id: symbol3
                objectName: "symbol3"
                x: 400
                y: 150
                width: 100
                height: 80

                //nameLabel.text: "3"
            }
            /**/

            /*REM*/
            TSP_Message
            {
                id: message1
                objectName: "message1"

                m_From: symbol1.bottomConnector
                m_To: symbol2.topConnector
            }

            TSP_Message
            {
                id: message2
                objectName: "message2"

                m_From: symbol1.bottomConnector
                m_To: symbol3.leftConnector
            }
            /**/

            /*REM
            Component.onCompleted:
            {
                rcPage.contentChildren.push(symbol1);
            }
            */
        }

        /**
        * Horizontal scrollbar
        */
        ScrollBar
        {
            // common properties
            id: hbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Horizontal
            size: rcPage.width / rcPageContent.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: vbar.width
        }

        /**
        * Vertical scrollbar
        */
        ScrollBar
        {
            // common properties
            id: vbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            size: rcPage.height / rcPageContent.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: hbar.height
        }

        /// called when page viewport width changed
        onWidthChanged:
        {
            hbar.size     = rcPage.width / rcPageContent.width
            hbar.position = Math.min(Math.max(hbar.position, 0.0), 1.0 - (hbar.size));
        }

        /// called when page viewport height changed
        onHeightChanged:
        {
            vbar.size     = rcPage.height / rcPageContent.height
            vbar.position = Math.min(Math.max(vbar.position, 0.0), 1.0 - (vbar.size));
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

    property int index: 0 // REM FIXME

    /**
    * Adds a message component to the document
    *@param from [var] - symbol the message is attached from
    *@param to [var] - symbol the message is attached to, if null the message is dragging
    *@param fromConn [var] - connector the message is attached from
    *@param toConn [var] - connector the message is attached to, if null the message is dragging
    */
    // todo FIXME -cFeature -oJean: Misplaced, should be moved to model view
    function addMessage(from, to)
    {
        // load the item component
        let component = Qt.createComponent('TSP_Message.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add message - an error occurred while the item was created - " + component.errorString());
            return;
        }

        // create and show new item object
        let item = component.createObject(rcPageContent, {"id":         "ctMessage" + index, //REM FIXME
                                                          "objectName": "ctMessage" + index,
                                                          "m_From":     from,
                                                          "m_To":       to});

        // REM
        console.log("Add message - new item - " + item.objectName);

        ++index;
        return item;
    }
}
