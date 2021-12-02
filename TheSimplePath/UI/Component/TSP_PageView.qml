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
    property alias pageViewport:  rcPageViewport
    property alias pageContainer: rcPageContainer
    property alias pageContent:   rcPageContent
    property alias horzScrollBar: sbHorz
    property alias vertScrollBar: sbVert

    // advanced properties
    property var  m_Page:            this
    property var  m_Model:           null
    property real m_ScaleFactor:     1
    property real m_ZoomMin:         0.5
    property real m_ZoomMax:         5.0
    property real m_AutoScrollSpeed: 0.0025
    property int  m_PageWidth:       794  // default A4 width in pixels, under 96 dpi
    property int  m_PageHeight:      1123 // default A4 height in pixels, under 96 dpi
    property int  m_GenIndex:        0

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
        // advanced properties
        property real m_SbHorzPos:  0
        property real m_SbHorzSize: rcPageViewport.width / rcPageContainer.width
        property real m_SbVertPos:  0
        property real m_SbVertSize: rcPageViewport.height / rcPageContainer.height

        // common properties
        id: rcPageViewport
        objectName: "rcPageViewport"
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
                let deltaX                 = (m_PrevX - mouseEvent.x) / rcPageContainer.width;
                rcPageViewport.m_SbHorzPos = JSHelper.clamp(rcPageViewport.m_SbHorzPos + deltaX, 0.0, 1.0 - (rcPageViewport.m_SbHorzSize));

                // calculate next vertical scroll position, and apply it
                let deltaY                 = (m_PrevY - mouseEvent.y) / rcPageContainer.height;
                rcPageViewport.m_SbVertPos = JSHelper.clamp(rcPageViewport.m_SbVertPos + deltaY, 0.0, 1.0 - (rcPageViewport.m_SbVertSize));

                m_PrevX = mouseEvent.x;
                m_PrevY = mouseEvent.y;
            }

            /// called when mouse wheel was rolled above page
            onWheel: function(mouseWheel)
            {
                // do change the zoom level?
                if (mouseWheel.modifiers & Qt.ControlModifier)
                {
                    // calculate the next scale factor and resize page
                    const offset  = mouseWheel.angleDelta.y * 0.001;
                    m_ScaleFactor = JSHelper.clamp(m_ScaleFactor + offset, m_ZoomMin, m_ZoomMax);

                    // notify page and children that the zoom level changed
                    rcPageContent.pageScaleChanged(m_ScaleFactor);
                    return;
                }

                // calculate next vertical scroll position, and apply it
                const offset = mouseWheel.angleDelta.y * 0.0001;

                if (mouseWheel.modifiers & Qt.ShiftModifier)
                    rcPageViewport.m_SbHorzPos = JSHelper.clamp(rcPageViewport.m_SbHorzPos - offset, 0.0, 1.0 - (rcPageViewport.m_SbHorzSize));
                else
                    rcPageViewport.m_SbVertPos = JSHelper.clamp(rcPageViewport.m_SbVertPos - offset, 0.0, 1.0 - (rcPageViewport.m_SbVertSize));

                mouseWheel.accepted = true;
            }
        }

        /**
        * Page container
        */
        Rectangle
        {
            // common properties
            id: rcPageContainer
            objectName: "rcPageContainer"
            x: (rcPageViewport.width  < width)  ? -sbHorz.position * width  : 0
            y: (rcPageViewport.height < height) ? -sbVert.position * height : 0
            width:  m_PageWidth  * m_ScaleFactor
            height: m_PageHeight * m_ScaleFactor

            /**
            * Page content
            */
            Rectangle
            {
                // advanced properties
                property bool m_DraggingMsg: false

                // signals
                signal doDisableMoveSize(var box)
                signal doAutoScroll(int minX, int maxX, int minY, int maxY)
                signal pageScaleChanged(double factor)

                // common properties
                id: rcPageContent
                objectName: "rcPageContent"
                color: "white"
                x: 0
                y: 0
                width: m_PageWidth
                height: m_PageHeight

                transform: Scale
                {
                    origin.x: 0
                    origin.y: 0
                    xScale: m_ScaleFactor
                    yScale: m_ScaleFactor
                }

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
                        for (let i = 0; i < height / step; ++i)
                        {
                            // draw a line of points
                            context.beginPath();
                            context.moveTo(0,         (i * step) + 1);
                            context.lineTo(width - 1, (i * step) + 1);
                            context.stroke();
                        }
                    }
                }

                /// called when auto-scroll should be applied
                onDoAutoScroll: function(minX, maxX, minY, maxY)
                {
                    // auto-scroll the page on x axis if the box exceeds its viewport limits
                    if (minX < Math.abs(rcPageContainer.x))
                        rcPageViewport.m_SbHorzPos =
                                JSHelper.clamp(rcPageViewport.m_SbHorzPos - m_AutoScrollSpeed, 0.0, 1.0 - rcPageViewport.m_SbHorzSize);
                    else
                    if (maxX > Math.abs(rcPageContainer.x) + rcPageViewport.width)
                        rcPageViewport.m_SbHorzPos =
                                JSHelper.clamp(rcPageViewport.m_SbHorzPos + m_AutoScrollSpeed, 0.0, 1.0 - rcPageViewport.m_SbHorzSize);

                    // auto-scroll the page on y axis if the box exceeds its viewport limits
                    if (minY < Math.abs(rcPageContainer.y))
                        rcPageViewport.m_SbVertPos =
                                JSHelper.clamp(rcPageViewport.m_SbVertPos - m_AutoScrollSpeed, 0.0, 1.0 - rcPageViewport.m_SbVertSize);
                    else
                    if (maxY > Math.abs(rcPageContainer.y) + rcPageViewport.height)
                        rcPageViewport.m_SbVertPos =
                                JSHelper.clamp(rcPageViewport.m_SbVertPos + m_AutoScrollSpeed, 0.0, 1.0 - rcPageViewport.m_SbVertSize);
                }

                /// called when page scale changed
                onPageScaleChanged:
                {
                    // recalculate the scroll position and size
                    rcPageViewport.m_SbHorzSize = rcPageViewport.width / rcPageContainer.width
                    rcPageViewport.m_SbHorzPos  = JSHelper.clamp(rcPageViewport.m_SbHorzPos, 0.0, 1.0 - rcPageViewport.m_SbHorzSize);
                    rcPageViewport.m_SbVertSize = rcPageViewport.height / rcPageContainer.height
                    rcPageViewport.m_SbVertPos  = JSHelper.clamp(rcPageViewport.m_SbVertPos, 0.0, 1.0 - rcPageViewport.m_SbVertSize);
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
            position: rcPageViewport.m_SbHorzPos
            size: rcPageViewport.m_SbHorzSize
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
            position: rcPageViewport.m_SbVertPos
            size: rcPageViewport.m_SbVertSize
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: sbHorz.height
        }

        /// called when page viewport width changed
        onWidthChanged:
        {
            rcPageViewport.m_SbHorzSize = rcPageViewport.width / rcPageContainer.width
            rcPageViewport.m_SbHorzPos  = JSHelper.clamp(rcPageViewport.m_SbHorzPos, 0.0, 1.0 - rcPageViewport.m_SbHorzSize);
        }

        /// called when page viewport height changed
        onHeightChanged:
        {
            rcPageViewport.m_SbVertSize = rcPageViewport.height / rcPageContainer.height
            rcPageViewport.m_SbVertPos  = JSHelper.clamp(rcPageViewport.m_SbVertPos, 0.0, 1.0 - rcPageViewport.m_SbVertSize);
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
                                                          "height":        height,
                                                          "m_ScaleFactor": m_ScaleFactor});

        console.log("Add box - succeeded - new item - " + item.objectName);

        ++m_GenIndex;
        return item;
    }

    /**
    * Adds a link component to the page
    *@param title [string] - link title
    *@param description [string] - link description
    *@param comments [string] - link comments
    *@param from [TSP_Connector] - connector belonging to box the link is attached from
    *@param to [TSP_Connector] - connector belonging to box the link is attached to, if null the link is dragging
    *@return [TSP_Link] added link, null on error
    */
    function addLink(title, description, comments, from, to)
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
        let item = component.createObject(rcPageContent, {"id":            "lkLink" + m_GenIndex,
                                                          "objectName":    "lkLink" + m_GenIndex,
                                                          "m_Title":       title,
                                                          "m_Description": description,
                                                          "m_Comments":    comments,
                                                          "m_From":        from,
                                                          "m_To":          to,
                                                          "m_ScaleFactor": m_ScaleFactor});

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
        return addLink("", "", "", from, to);
    }
}
