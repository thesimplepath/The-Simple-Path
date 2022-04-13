import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

// javascript
import "js/TSP_JSHelper.js" as JSHelper

// c++
import thesimplepath.proxys 1.0

/**
* Box, it's a basic component which can be moved and resized, and contain connectors
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias boxProxy:        bpBoxProxy
    property alias titleText:       txTitle
    property alias descriptionText: txDescription
    property alias commentsText:    txComments
    property alias rectContents:    rcContent
    property alias rectConnectors:  rcConnectors
    property alias leftConnector:   coLeft
    property alias topConnector:    coTop
    property alias rightConnector:  coRight
    property alias bottomConnector: coBottom

    // advanced properties
    property var    m_PageContent:       undefined
    property string m_Color:             Styles.m_BoxBorderColor
    property string m_BgColor:           Styles.m_BoxBgColor
    property string m_TextColor:         Styles.m_DarkTextColor
    property string m_HandleColor:       Styles.m_BoxHandleBgColor
    property string m_HandleBorderColor: Styles.m_BoxHandleBorderColor
    property string m_FontFamily:        Styles.m_ComponentFont.m_Family
    property real   m_ScaleFactor:       1
    property int    m_MouseStartX:       0
    property int    m_MouseStartY:       0
    property int    m_FontSize:          Styles.m_ComponentFont.m_Size
    property int    m_BorderWidth:       Styles.m_BoxBorderWidth
    property int    m_Radius:            Styles.m_BoxRadius
    property int    m_TextMargin:        Styles.m_BoxTextMargin

    // common properties
    id: ctBox
    objectName: "ctBox"

    // signals
    signal doAddItem(var type, var uid)
    signal doRemoveItem(var uid)
    signal moveStart()
    signal move(int deltaX, int deltaY)
    signal moveEnd()
    signal resize(int direction, int deltaX, int deltaY)
    signal dblClick()

    /**
    * Box proxy
    *@note This component will auto-create a new c++ TSP_QmlBoxProxy instance
    */
    BoxProxy
    {
        id: bpBoxProxy
        objectName: "bpBoxProxy"

        /// Called when a custom item should be added to the box
        onAddItemToBox: function(type, uid)
        {
            ctBox.doAddItem(type, uid);
        }

        /// Called when an item should be removed from the box
        onRemoveItemFromBox: function(type, uid)
        {
            ctBox.doRemoveItem(type, uid);
        }
    }

    /**
    * Connectors
    */
    Rectangle
    {
        // common properties
        id: rcConnectors
        objectName: "rcConnectors"
        anchors.fill: parent
        color: "transparent"
        z: -2

        /**
        * Left connector
        */
        TSP_Connector
        {
            // common properties
            id: coLeft
            objectName: "coLeft"
            x:   parent.x - (width + 2)
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: true

            // advanced properties
            m_Box:         rcConnectors.parent
            m_Position:    TSP_Connector.IEPosition.IE_P_Left
            m_ScaleFactor: ctBox.m_ScaleFactor;
        }

        /**
        * Top connector
        */
        TSP_Connector
        {
            // common properties
            id: coTop
            objectName: "coTop"
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:   parent.y - (height + 2)
            visible: true

            // advanced properties
            m_Box:         rcConnectors.parent
            m_Position:    TSP_Connector.IEPosition.IE_P_Top
            m_ScaleFactor: ctBox.m_ScaleFactor;
        }

        /**
        * Right connector
        */
        TSP_Connector
        {
            // common properties
            id: coRight
            objectName: "coRight"
            x:   parent.x + parent.width + 2
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: true

            // advanced properties
            m_Box:         rcConnectors.parent
            m_Position:    TSP_Connector.IEPosition.IE_P_Right
            m_ScaleFactor: ctBox.m_ScaleFactor;
        }

        /**
        * Bottom connector
        */
        TSP_Connector
        {
            // common properties
            id: coBottom
            objectName: "coBottom"
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:   parent.y + parent.height + 2
            visible: true

            // advanced properties
            m_Box:         rcConnectors.parent
            m_Position:    TSP_Connector.IEPosition.IE_P_Bottom
            m_ScaleFactor: ctBox.m_ScaleFactor;
        }
    }

    /**
    * Box background, also handles gesture
    */
    TSP_HandleControl
    {
        // common properties
        id: hcBackground
        objectName: "hcBackground"
        anchors.fill: parent
        z: ctBox.activeFocus ? 0 : -1

        // advanced properties
        m_Target: ctBox
        m_HandleColor: ctBox.m_HandleColor
        m_HandleBorderColor: ctBox.m_HandleBorderColor
        m_BorderColor: ctBox.m_Color
        m_BorderWidth: ctBox.m_BorderWidth
        m_Radius: ctBox.m_Radius
        m_HandleVisible: ctBox.activeFocus
    }

    /**
    * Box content
    */
    Rectangle
    {
        // common properties
        id: rcContent
        objectName: "rcContent"
        anchors.fill: parent
        color: ctBox.m_BgColor
        radius: ctBox.m_Radius >= ctBox.m_BorderWidth ? ctBox.m_Radius - ctBox.m_BorderWidth : 0
        anchors.margins: ctBox.m_BorderWidth
        z: ctBox.activeFocus ? -1 : 0
        clip: true

        /**
        * Title label
        */
        Text
        {
            // common properties
            id:                  txTitle
            objectName:          "txTitle"
            text:                bpBoxProxy.title
            anchors.left:        parent.left
            anchors.leftMargin:  m_TextMargin
            anchors.top:         parent.top
            anchors.right:       parent.right
            anchors.rightMargin: m_TextMargin
            font.family:         m_FontFamily
            font.pointSize:      m_FontSize
            wrapMode:            Text.WordWrap
            color:               m_TextColor
            clip:                true
        }

        /**
        * Description label
        */
        Text
        {
            // common properties
            id:                  txDescription
            objectName:          "txDescription"
            text:                bpBoxProxy.description
            anchors.left:        parent.left
            anchors.leftMargin:  m_TextMargin
            anchors.top:         txTitle.bottom
            anchors.right:       parent.right
            anchors.rightMargin: m_TextMargin
            font.family:         m_FontFamily
            font.pointSize:      m_FontSize
            wrapMode:            Text.WordWrap
            color:               m_TextColor
            clip:                true
        }

        /**
        * Comments label
        */
        Text
        {
            // common properties
            id:                  txComments
            objectName:          "txComments"
            text:                bpBoxProxy.comments
            anchors.left:        parent.left
            anchors.leftMargin:  m_TextMargin
            anchors.top:         txDescription.bottom
            anchors.right:       parent.right
            anchors.rightMargin: m_TextMargin
            font.family:         m_FontFamily
            font.pointSize:      m_FontSize
            wrapMode:            Text.WordWrap
            color:               m_TextColor
            clip:                true
        }

        /**
        * Split view mouse area
        */
        MouseArea
        {
            // common properties
            id: maMouseArea
            objectName: "maMouseArea"
            anchors.fill: parent

            /// called when the view is clicked
            onClicked:
            {
                ctBox.forceActiveFocus();
            }
        }
    }

    /// Called when box starts to move
    onMoveStart: function()
    {
        m_MouseStartX = x;
        m_MouseStartY = y;
    }

    /// Called when box is moving
    onMove: function(deltaX, deltaY)
    {
        if (!m_PageContent)
            return;

        // move box and limit it in owning page
        x += deltaX;
        x  = JSHelper.clamp(x, 0, m_PageContent.width - width);
        y += deltaY;
        y  = JSHelper.clamp(y, 0, m_PageContent.height - height);

        const boxX      = x      * m_ScaleFactor;
        const boxY      = y      * m_ScaleFactor;
        const boxWidth  = width  * m_ScaleFactor;
        const boxHeight = height * m_ScaleFactor;

        // notify that auto-scroll may be applied
        m_PageContent.doAutoScroll(boxX, boxX + boxWidth, boxY, boxY + boxHeight);
    }

    /// Called when box ends to move
    onMoveEnd: function()
    {
        // was control dragged?
        if (Math.abs(x - m_MouseStartX) >= 5 || Math.abs(y - m_MouseStartY) >= 5)
            return;

        if (m_PageContent)
            m_PageContent.doDisableMoveSize(this);
    }

    /// Called when box should be resized
    onResize: function(direction, deltaX, deltaY)
    {
        // resize box width
        if (deltaX)
            switch (direction)
            {
                case TSP_Handle.IEDirection.IE_D_Left:
                case TSP_Handle.IEDirection.IE_D_LeftTop:
                case TSP_Handle.IEDirection.IE_D_LeftBottom:
                    x     += deltaX;
                    width -= deltaX;

                    if (x < 0 || width < 30)
                    {
                        x     -= deltaX;
                        width += deltaX;
                    }

                    break;

                case TSP_Handle.IEDirection.IE_D_Right:
                case TSP_Handle.IEDirection.IE_D_RightTop:
                case TSP_Handle.IEDirection.IE_D_RightBottom:
                    width += deltaX;

                    if (width < 30)
                        width -= deltaX;

                    break;
            }

        // resize box height
        if (deltaY)
            switch (direction)
            {
                case TSP_Handle.IEDirection.IE_D_Top:
                case TSP_Handle.IEDirection.IE_D_LeftTop:
                case TSP_Handle.IEDirection.IE_D_RightTop:
                    y      += deltaY;
                    height -= deltaY;

                    if (y < 0 || height < 30)
                    {
                        y      -= deltaY;
                        height += deltaY;
                    }

                    break;

                case TSP_Handle.IEDirection.IE_D_Bottom:
                case TSP_Handle.IEDirection.IE_D_LeftBottom:
                case TSP_Handle.IEDirection.IE_D_RightBottom:
                    height += deltaY;

                    if (height < 30)
                        height -= deltaY;

                    break;
            }
    }

    /// Called when box is double clicked
    onDblClick: function()
    {}

    /**
    * Page content signal connections
    */
    Connections
    {
        // common properties
        target: pageContent

        /**
        * Called when the page scale factor changed
        *@param {number} factor - scale factor
        */
        function onPageScaleChanged(factor)
        {
            m_ScaleFactor = factor;
        }
    }

    /**
    * Box proxy signal connections
    */
    Connections
    {
        // common properties
        target: bpBoxProxy

        /**
        * Called when the title changed
        *@param title - new title
        */
        function onTitleChanged(title)
        {
            if (!txTitle.visible)
                return;

            txTitle.text = title;
        }

        /**
        * Called when the description changed
        *@param description - new description
        */
        function onDescriptionChanged(description)
        {
            if (!txDescription.visible)
                return;

            txDescription.text = description;
        }

        /**
        * Called when the comments changed
        *@param comments - new comments
        */
        function onCommentsChanged(comments)
        {
            if (!txComments.visible)
                return;

            txComments.text = comments;
        }
    }
}
