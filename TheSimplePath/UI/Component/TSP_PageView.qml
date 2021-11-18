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
    // aliases
    property alias pageContent:   rcPageContent
    property alias horzScrollBar: sbHorz
    property alias vertScrollBar: sbVert

    // advanced properties
    property var m_Page:     this
    property var m_Model:    null
    property int m_GenIndex: 0

    // signals
    signal linkAdded(var link)
    signal linkCanceled()

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
                sbHorz.position = JSHelper.clamp(sbHorz.position + deltaX, 0.0, 1.0 - (sbHorz.size));

                // calculate next vertical scroll position, and apply it
                let deltaY    = (m_PrevY - mouseEvent.y) / rcPageContent.height;
                sbVert.position = JSHelper.clamp(sbVert.position + deltaY, 0.0, 1.0 - (sbVert.size));

                m_PrevX = mouseEvent.x;
                m_PrevY = mouseEvent.y;
            }

            /// called when mouse wheel was rolled above page
            onWheel: function(mouseWheel)
            {
                let offset    = mouseWheel.angleDelta.y * 0.0001;
                sbVert.position = Math.min(Math.max(sbVert.position - offset, 0.0), 1.0 - (sbVert.size));

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
            x: -sbHorz.position * width
            y: -sbVert.position * height
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
        }

        /**
        * Horizontal scrollbar
        */
        ScrollBar
        {
            // common properties
            id: sbHorz
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Horizontal
            size: rcPage.width / rcPageContent.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: sbVert.width
        }

        /**
        * Vertical scrollbar
        */
        ScrollBar
        {
            // common properties
            id: sbVert
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            size: rcPage.height / rcPageContent.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: sbHorz.height
        }

        /// called when page viewport width changed
        onWidthChanged:
        {
            sbHorz.size     = rcPage.width / rcPageContent.width
            sbHorz.position = Math.min(Math.max(sbHorz.position, 0.0), 1.0 - (sbHorz.size));
        }

        /// called when page viewport height changed
        onHeightChanged:
        {
            sbVert.size     = rcPage.height / rcPageContent.height
            sbVert.position = Math.min(Math.max(sbVert.position, 0.0), 1.0 - (sbVert.size));
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

    /**
    * Adds a box component to the page
    *@param title [string] - box title
    *@param description [string] - box description
    *@param comments [string] - box comments
    *@param x [number] - component x position, in pixels
    *@param y [number] - component y position, in pixels
    *@param width [number] - component width, in pixels
    *@param height [number] - component height, in pixels
    *@return [TSP_Box] added box, null on error
    */
    function addBox(title, description, comments, x, y, width, height)
    {
        // load the item component
        let component = Qt.createComponent('TSP_Box.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add box - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        // create and show new item object
        let item = component.createObject(rcPageContent, {"id":            "bxBox" + m_GenIndex,
                                                          "objectName":    "bxBox" + m_GenIndex,
                                                          "m_Title":       title,
                                                          "m_Description": description,
                                                          "m_Comments":    comments,
                                                          "x":             x,
                                                          "y":             y,
                                                          "width":         width,
                                                          "height":        height});

        console.log("Add box - succeeded - new item - " + item.objectName);

        ++m_GenIndex;
        return item;
    }

    /**
    * Adds a link component to the page
    *@param title [string] - link title
    *@param from [TSP_Connector] - connector belonging to box the link is attached from
    *@param to [TSP_Connector] - connector belonging to box the link is attached to, if null the link is dragging
    *@return [TSP_Link] added link, null on error
    */
    function addLink(title, from, to)
    {
        // load the item component
        let component = Qt.createComponent('TSP_Link.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add link - an error occurred while the item was created - " + component.errorString());

            // emit signal that link adding was canceled
            if (to)
                linkCanceled();

            return null;
        }

        // create and show new item object
        let item = component.createObject(rcPageContent, {"id":         "lkLink" + m_GenIndex,
                                                          "objectName": "lkLink" + m_GenIndex,
                                                          "m_Title":    title,
                                                          "m_From":     from,
                                                          "m_To":       to});

        // emit signal and log only if destination connector is defined
        if (to)
        {
            // emit signal that link was added
            linkAdded(item);

            console.log("Add link - succeeded - new item - " + item.objectName);
        }

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
        return addLink("", from, to);
    }
}
