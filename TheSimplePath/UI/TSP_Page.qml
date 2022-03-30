import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.1
import QtQuick.Templates 2.15 as T

// javascript
import "js/TSP_JSHelper.js" as JSHelper

// c++
import thesimplepath.proxys 1.0

/**
* Page view
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Box default position type
    *@note This enum is linked with the one located in TSP_QmlPageProxy.
    *      Don't modify it without updating its twin
    */
    enum IEBoxPosition
    {
        IE_BP_Default = 0,
        IE_BP_Centered,
        IE_BP_Custom
    }

    // aliases
    property alias pageProxy:     ppPageProxy
    property alias pageViewport:  rcPageViewport
    property alias pageContainer: rcPageContainer
    property alias pageContent:   rcPageContent
    property alias horzScrollBar: sbHorz
    property alias vertScrollBar: sbVert

    // advanced properties
    property var    m_Page:            this
    property real   m_ScaleFactor:     1
    property real   m_ZoomMin:         0.5
    property real   m_ZoomMax:         5.0
    property real   m_AutoScrollSpeed: 0.0025
    property int    m_PageWidth:       794  // default A4 width in pixels, under 96 dpi
    property int    m_PageHeight:      1123 // default A4 height in pixels, under 96 dpi
    property int    m_DefX:            10
    property int    m_DefY:            10

    // signals
    signal doAddBox(var type, var uid, var position, var x, var y, var width, var height)
    signal doAddLink(var type, var uid, var startUID, var startPos, var endUID, var endPos, var x, var y, var width, var height)
    signal linkAdded(var link)
    signal linkCanceled()

    // common properties
    id:         ctPageView
    objectName: "ctPageView"

    /**
    * Question message dialog asking to user if the associated links should be deleted with the box
    */
    MessageDialog
    {
        // properties
        property var m_Box: undefined

        // common properties
        id: mdConfirmDelLinks
        objectName: "mdConfirmDelLinks"
        title: qsTrId("delete-attached-links-title")
        text: qsTrId("delete-attached-links-text")
        detailedText: qsTrId("delete-attached-links-detailed-text")
        icon: StandardIcon.Question
        standardButtons: StandardButton.Yes | StandardButton.No
        visible: false

        /// called when user clicked on the Yes button
        onYes:
        {
            console.log("Delete selected component - box - user ACCEPTED to delete attached links");

            // delete box and attached links
            deleteBox(m_Box, true);

            // close the dialog box
            close();
        }

        /// called when user clicked on the No button
        onNo:
        {
            console.log("Delete selected component - box - user REFUSED to delete attached links - CANCELED");

            // close the dialog box
            close();
        }
    }

    /**
    * Page proxy
    *@note This component will auto-create a new c++ TSP_QmlPageProxy instance
    */
    PageProxy
    {
        id: ppPageProxy
        objectName: "ppPageProxy"

        /// Called when a box should be added to the view
        onAddBoxToView: function(type, uid, position, x, y, width, height)
        {
            // search for box type to create
            switch (type)
            {
                case "":
                case "box":
                {
                    // calculate the box position
                    const [xPos, yPos] = getBoxPosition(position, x, y, width, height);

                    // add a box to the page
                    let box = addBox(xPos, yPos, width, height, uid);

                    // notify if the box was added successfully
                    onBoxAdded(box);

                    return;
                }

                default:
                    ctPageView.doAddBox(type, uid, position, x, y, width, height);
                    return;
            }
        }

        /// Called when a link should be added to the view
        onAddLinkToView: function(type, uid, startUID, startPos, endUID, endPos, x, y, width, height)
        {
            // search for link type to create
            switch (type)
            {
                case "":
                case "link":
                {
                    // no start box unique identifier?
                    if (!startUID || !startUID.length)
                    {
                        console.log("onAddLinkToView - FAILED - start box is undefined");
                        return;
                    }

                    // get the start box on the interface
                    let startBox = getBoxOrLink(startUID);

                    // found it?
                    if (!startBox)
                    {
                        console.log("onAddLinkToView - FAILED - start box could not be retrieved");
                        return;
                    }

                    let startConnector = undefined;

                    // get the start connector
                    switch (startPos)
                    {
                        case TSP_Connector.IEPosition.IE_P_Left:   startConnector = startBox.leftConnector;   break;
                        case TSP_Connector.IEPosition.IE_P_Top:    startConnector = startBox.topConnector;    break;
                        case TSP_Connector.IEPosition.IE_P_Right:  startConnector = startBox.rightConnector;  break;
                        case TSP_Connector.IEPosition.IE_P_Bottom: startConnector = startBox.bottomConnector; break;

                        default:
                        {
                            console.log("onAddLinkToView - FAILED - start connector could not be retrieved");
                            return;
                        }
                    }

                    let endConnector = undefined;

                    // no end box unique identifier?
                    if (endUID && endUID.length)
                    {
                        // get the end box on the interface
                        let endBox = getBoxOrLink(endUID);

                        // found it?
                        if (!endBox)
                        {
                            console.log("onAddLinkToView - FAILED - end box could not be retrieved");
                            return;
                        }

                        // get the end connector
                        switch (endBox)
                        {
                            case TSP_Connector.IEPosition.IE_P_Left:   endConnector = endBox.leftConnector;   break;
                            case TSP_Connector.IEPosition.IE_P_Top:    endConnector = endBox.topConnector;    break;
                            case TSP_Connector.IEPosition.IE_P_Right:  endConnector = endBox.rightConnector;  break;
                            case TSP_Connector.IEPosition.IE_P_Bottom: endConnector = endBox.bottomConnector; break;

                            default:
                            {
                                console.log("onAddLinkToView - FAILED - end connector could not be retrieved");
                                return;
                            }
                        }
                    }

                    // add the link on the interface
                    let link = addLink(startConnector, endConnector, x, y, width, height, uid);

                    // notify if the link was added successfully
                    onLinkAdded(link);

                    return;
                }

                default:
                    ctPageView.doAddLink(type, uid, startUID, startPos, endUID, endPos, x, y, width, height);
                    return;
            }
        }

        /// Called when a component should be removed from the page
        onRemoveComponentView: function(uid)
        {
            removeComponent(uid);
        }
    }

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

            /// Called when mouse is pressed above page
            onPressed: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.forceActiveFocus(true);

                m_PrevX   = mouseEvent.x;
                m_PrevY   = mouseEvent.y;
                m_Panning = true;
            }

            /// Called when mouse is released after been pressed above page
            onReleased: function(mouseEvent)
            {
                m_Panning = false;
            }

            /// Called when mouse position changed above page
            onPositionChanged: function(mouseEvent)
            {
                // do nothing if mouse button is not pressed
                if (!pressed)
                    return;

                // calculate next horizontal scroll position, and apply it
                const deltaX               = (m_PrevX - mouseEvent.x) / rcPageContainer.width;
                rcPageViewport.m_SbHorzPos = JSHelper.clamp(rcPageViewport.m_SbHorzPos + deltaX, 0.0, 1.0 - (rcPageViewport.m_SbHorzSize));

                // calculate next vertical scroll position, and apply it
                const deltaY               = (m_PrevY - mouseEvent.y) / rcPageContainer.height;
                rcPageViewport.m_SbVertPos = JSHelper.clamp(rcPageViewport.m_SbVertPos + deltaY, 0.0, 1.0 - (rcPageViewport.m_SbVertSize));

                m_PrevX = mouseEvent.x;
                m_PrevY = mouseEvent.y;
            }

            /// Called when mouse wheel was rolled above page
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
                color: "transparent"
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

                    /// Called when canvas is painted
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

                /// Called when auto-scroll should be applied
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

                /// Called when page scale changed
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

    /// called when the delete key is pressed
    Keys.onDeletePressed: function(keyEvent)
    {
        console.log("GUI - delete selected component");

        // get selected item
        const selectedItem = getSelected();

        // no selection?
        if (!selectedItem)
        {
            console.log("Delete selected component - no selection");
            return;
        }

        // is selection a box or a link?
        if (selectedItem instanceof TSP_Box)
        {
            console.log("Delete selected component - box - " + selectedItem.boxProxy.uid);

            // is box connected to something?
            if (selectedItem.leftConnector.m_Links.length  ||
                selectedItem.topConnector.m_Links.length   ||
                selectedItem.rightConnector.m_Links.length ||
                selectedItem.bottomConnector.m_Links.length)
            {
                console.log("Delete selected component - box - several links attached - confirm with user");

                // show the "Do delete attached links?" dialog box
                mdConfirmDelLinks.m_Box = selectedItem;
                mdConfirmDelLinks.open();
                return;
            }

            // delete box
            deleteBox(selectedItem, false);
        }
        else
        if (selectedItem instanceof TSP_Link)
            // delete link
            deleteLink(selectedItem);
    }

    /**
    * Calculates the next available default position
    */
    function calculateNextDefPos()
    {
        m_DefX += 10;
        m_DefY += 10;

        if (m_DefX > 100)
            m_DefX = 10;

        if (m_DefY > 100)
            m_DefY = 10;
    }

    /**
    * Gets the box position
    *@param {IEBoxPosition} position - the position type to apply
    *@param {number} x - proposed x position
    *@param {number} y - proposed y position
    *@param {number} width - box width
    *@param {number} height - box height
    *@return box [x, y] position
    */
    function getBoxPosition(position, x, y, width, height)
    {
        // calculate default position
        let xPos;
        let yPos;

        // get the x and y position on the page where the viewport is located
        let xPage = (rcPageViewport.m_SbHorzPos * m_PageWidth);
        let yPage = (rcPageViewport.m_SbVertPos * m_PageHeight);

        // is x position out of bounds?
        if (xPage < 0)
            xPage = 0;

        // is y position out of bounds?
        if (yPage < 0)
            yPage = 0;

        // search for position type to apply
        switch (position)
        {
            case TSP_PageView.IEBoxPosition.IE_BP_Default:
                // default position, align to page viewport left and top
                xPos = xPage + m_DefX;
                yPos = yPage + m_DefY;

                // update the default position offsets
                calculateNextDefPos();
                break;

            case TSP_PageView.IEBoxPosition.IE_BP_Centered:
            {
                // calculate the scaled page size and the total size
                const scaledPageW = m_PageWidth  * m_ScaleFactor;
                const scaledPageH = m_PageHeight * m_ScaleFactor;
                const totalWidth  = (scaledPageW < rcPageViewport.width)  ? scaledPageW : rcPageViewport.width;
                const totalHeight = (scaledPageH < rcPageViewport.height) ? scaledPageH : rcPageViewport.height;

                // centered position, align to the center of the page viewport
                xPos = xPage + (((totalWidth  / 2) - ((width  * m_ScaleFactor) / 2)) / m_ScaleFactor);
                yPos = yPage + (((totalHeight / 2) - ((height * m_ScaleFactor) / 2)) / m_ScaleFactor);
                break;
            }

            case TSP_PageView.IEBoxPosition.IE_BP_Custom:
            {
                // custom position
                xPos = x;
                yPos = y;

                let doUseDefPos = false;

                // if x is undefined (i.e -1), use the default one
                if (xPos < 0)
                {
                    xPos        = xPage + m_DefX;
                    doUseDefPos = true;
                }

                // if y is undefined (i.e -1), use the default one
                if (yPos < 0)
                {
                    yPos        = yPage + m_DefY;
                    doUseDefPos = true;
                }

                // if a default position was used, update the default position offsets
                if (doUseDefPos)
                    calculateNextDefPos();

                break;
            }

            default:
                // no position defined
                xPos = 0;
                yPos = 0;
                break;
        }

        // limit the box position in the page bounds
        xPos = JSHelper.clamp(xPos, 0, rcPageContent.width  - width);
        yPos = JSHelper.clamp(yPos, 0, rcPageContent.height - height);

        return [xPos, yPos];
    }

    /**
    * Gets a box or a link by its unique identifier
    *@param {string} uid - unique identifier to search
    *@return box or link, undefined if not found or on error
    */
    function getBoxOrLink(uid)
    {
        if (!uid || !uid.length)
        {
            console.error("getBoxOrLink - FAILED - uid is undefined");
            return undefined;
        }

        // iterate through page children
        for (var i = 0; i < rcPageContent.children.length; ++i)
            // is component a box or link?
            if (rcPageContent.children[i] instanceof TSP_Box)
            {
                // found the matching component?
                if (rcPageContent.children[i].boxProxy.uid === uid)
                    return rcPageContent.children[i];
            }
            else
            if (rcPageContent.children[i] instanceof TSP_Link)
                // found the matching component?
                if (rcPageContent.children[i].linkProxy.uid === uid)
                    return rcPageContent.children[i];

        return undefined;
    }

    /**
    * Gets the currently selected item on page
    *@return the currently selected item on page, undefined if no selection
    */
    function getSelected()
    {
        // iterate through page children
        for (var i = 0; i < rcPageContent.children.length; ++i)
            // is component a box or link?
            if (rcPageContent.children[i] instanceof TSP_Box)
            {
                // found the active box?
                if (rcPageContent.children[i].activeFocus)
                    return rcPageContent.children[i];
            }
            else
            if (rcPageContent.children[i] instanceof TSP_Link)
                // found the active link?
                if (rcPageContent.children[i].background.activeFocus)
                    return rcPageContent.children[i];

        return undefined;
    }

    /**
    * Adds a box component to the page
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    *@param {string} uid - box unique identifier
    *@return {TSP_Box} added box, undefined on error
    */
    function addBox(x, y, width, height, uid)
    {
        // load the item component
        let component = Qt.createComponent('TSP_Box.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add box - an error occurred while the item was created - " + component.errorString());
            return undefined;
        }

        // build box identifier
        const boxId = "bxBox_" + uid;

        // create and show new item object
        let item = component.createObject(rcPageContent, {"id":            boxId,
                                                          "objectName":    boxId,
                                                          "x":             x,
                                                          "y":             y,
                                                          "width":         width,
                                                          "height":        height,
                                                          "m_ScaleFactor": m_ScaleFactor});

        // succeeded?
        if (!item)
        {
            console.error("Add box - an error occurred while the item was added to page");
            return undefined;
        }

        // declare the unique identifier in the box proxy
        item.boxProxy.uid = uid;

        console.log("Add box - succeeded - new item - " + item.objectName);

        return item;
    }

    /**
    * Adds a link component to the page
    *@param {TSP_Connector} from - connector belonging to box the link is attached from
    *@param {TSP_Connector} to - connector belonging to box the link is attached to, if undefined the link is dragging
    *@param {number} x - label x position, in pixels
    *@param {number} y - label y position, in pixels
    *@param {number} width - label width, in pixels
    *@param {number} height - label height, in pixels
    *@param {string} uid - link unique identifier
    *@return {TSP_Link} added link, undefined on error
    */
    function addLink(from, to, x, y, width, height, uid)
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

            return undefined;
        }

        // build link identifier
        const linkId = "lkLink_" + uid;

        // create and show new item object
        let item = component.createObject(rcPageContent, {"id":            linkId,
                                                          "objectName":    linkId,
                                                          "m_From":        from,
                                                          "m_To":          to,
                                                          "m_ScaleFactor": m_ScaleFactor});

        // succeeded?
        if (!item)
        {
            console.error("Add link - an error occurred while the item was added to page");
            return undefined;
        }

        // declare the unique identifier in the link proxy
        item.linkProxy.uid = uid;

        if (x >= 0 && y >= 0)
            item.m_LabelPos = Qt.vector2d(x, y);

        if (width >= 0 && height >= 0)
            item.m_LabelSize = Qt.vector2d(width, height);

        // emit signal and log only if destination connector is defined
        if (to)
        {
            // emit signal that link was added
            linkAdded(item);

            console.log("Add link - succeeded - new item - " + item.objectName);
        }

        return item;
    }

    /**
    * Called when starting to add a link
    *@param {TSP_Connector} from - connector belonging to box the link starts from
    *@return {TSP_Link} added link, undefined on error
    */
    function startAddLink(from)
    {
        // notify the page proxy that a link adding starts, and get the newly created link unique identifier
        const linkUID = ppPageProxy.onAddLinkStart(from.m_Box.boxProxy.uid, from.m_Position);

        // failed?
        if (!linkUID || !linkUID.length)
        {
            console.log("Start add link - FAILED - link object could not be created");

            // emit signal that link adding was canceled
            linkCanceled();

            return undefined;
        }

        // get the link on the interface
        let link = getBoxOrLink(linkUID);

        // found it?
        if (!link)
        {
            console.log("Start add link - FAILED - link object could not be retrieved on the interface");

            // emit signal that link adding was canceled
            linkCanceled();

            return undefined;
        }

        return link;
    }

    /**
    * Deletes a box
    *@param box - box to delete
    *@param doDelAttachedLinks - if true, attached links will also be deleted
    */
    function deleteBox(box, doDelAttachedLinks)
    {
        if (!box)
            return;

        // do delete attached links?
        if (doDelAttachedLinks)
        {
            // delete left links
            for (let i = box.leftConnector.m_Links.length - 1; i >= 0; --i)
                deleteLink(box.leftConnector.m_Links[i]);

            // delete top links
            for (let i = box.topConnector.m_Links.length - 1; i >= 0; --i)
                deleteLink(box.topConnector.m_Links[i]);

            // delete right links
            for (let i = box.rightConnector.m_Links.length - 1; i >= 0; --i)
                deleteLink(box.rightConnector.m_Links[i]);

            // delete bottom links
            for (let i = box.bottomConnector.m_Links.length - 1; i >= 0; --i)
                deleteLink(box.bottomConnector.m_Links[i]);
        }

        // delete box
        ppPageProxy.onDeleteBox(box.boxProxy.uid);
    }

    /**
    * Deletes a link
    *@param link - link to delete
    */
    function deleteLink(link)
    {
        if (!link)
            return;

        // unbind link from start box
        if (link.m_From)
            link.unbindMsgFromBox(link.m_From.m_Box);

        // unbind link from end box
        if (link.m_To)
            link.unbindMsgFromBox(link.m_To.m_Box);

        ppPageProxy.onDeleteLink(link.linkProxy.uid);
    }

    /**
    * Removes a component from the page
    *@param {string} uid - component unique identifier to remove
    */
    function removeComponent(uid)
    {
        // get the component to remove from the interface
        let component = getBoxOrLink(uid);

        // found it?
        if (!component)
            return;

        console.log("Remove component - uid - " + uid);

        // iterate through page view stack until find the view to delete, and deletes it
        for (var i = rcPageContent.children.length - 1; i >= 0; --i)
            // found the component to delete?
            if ((rcPageContent.children[i] instanceof TSP_Box    &&
                !rcPageContent.children[i].m_Deleted             &&
                 rcPageContent.children[i].boxProxy.uid === uid) ||
                (rcPageContent.children[i] instanceof TSP_Link   &&
                !rcPageContent.children[i].m_Deleted             &&
                 rcPageContent.children[i].linkProxy.uid === uid))
                {
                    // NOTE setting the deleted property just before destroying the component may seem incoherent,
                    // however the destroyed item is kept in memory until the garbage collector deletes it, and may
                    // be thus still found when the children are iterated. This may cause a deleting item to be
                    // processed as a normal item in other situations where it shouldn't
                    rcPageContent.children[i].m_Deleted = true;
                    rcPageContent.children[i].destroy();
                    break;
                }

        console.log("Remove component - succeeded");
    }
}
