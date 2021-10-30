import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Templates 2.15 as T

/**
* Message, it's a link between 2 symbols
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_From:        null // box start connector at which message is attached
    property var m_To:          null // box end connector at which message is attached, if null message is dragging
    property var m_StartPoint:  getStartPoint()
    property var m_CenterPoint: getCenterPoint()
    property var m_EndPoint:    getEndPoint()
    property var m_LabelPos:    Qt.vector2d(m_StartPoint.x + (((m_EndPoint.x - m_StartPoint.x) / 2.0) - (m_LabelSize.x / 2.0)),
                                            m_StartPoint.y + (((m_EndPoint.y - m_StartPoint.y) / 2.0) - (m_LabelSize.y / 2.0)))
    property var m_LabelSize:   Qt.vector2d(100, 50)
    property var m_ArrowSize:   Qt.vector2d(3, 10)
    property int m_Margin:      2

    // common properties
    id: itMessage
    objectName: "itMessage"
    anchors.fill: parent

    /**
    * First connection line
    */
    Shape
    {
        // common properties
        id:            shMsgFromLine
        objectName:    "shMsgFromLine"
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        clip:          false

        /**
        * First connection line path
        */
        ShapePath
        {
            // common properties
            id:          spMsgFromLine
            objectName:  "spMsgFromLine"
            strokeColor: "#202020"
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      m_StartPoint.x
            startY:      m_StartPoint.y

            /**
            * Line path
            */
            PathLine { x: m_CenterPoint.x; y: m_CenterPoint.y }
        }
    }

    /**
    * Second connection line
    */
    Shape
    {
        // common properties
        id:            shMsgToLine
        objectName:    "shMsgToLine"
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        clip:          false

        /**
        * Second connection line path
        */
        ShapePath
        {
            // common properties
            id:          spMsgToLine
            objectName:  "spMsgToLine"
            strokeColor: "#202020"
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      m_CenterPoint.x
            startY:      m_CenterPoint.y

            /**
            * Line path
            */
            PathLine { x: m_EndPoint.x; y: m_EndPoint.y }
        }

        /**
        * Arrow
        */
        ShapePath
        {
            property var m_Dir:    Qt.vector2d(m_EndPoint.x - m_CenterPoint.x, m_EndPoint.y - m_CenterPoint.y).normalized()
            property var m_DirCCW: Qt.vector2d(-m_Dir.y,  m_Dir.x)
            property var m_DirCW:  Qt.vector2d( m_Dir.y, -m_Dir.x)

            // common properties
            id:          spMsgArrow
            objectName:  "spMsgArrow"
            strokeColor: "#202020"
            fillColor:   "#202020"
            strokeWidth: 1
            startX:      m_CenterPoint.x
            startY:      m_CenterPoint.y

            /**
            * Arrow path
            */
            PathMove { x: m_EndPoint.x; y: m_EndPoint.y }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spMsgArrow.m_Dir.x) + (m_ArrowSize.x * spMsgArrow.m_DirCCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spMsgArrow.m_Dir.y) + (m_ArrowSize.x * spMsgArrow.m_DirCCW.y) }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spMsgArrow.m_Dir.x) + (m_ArrowSize.x * spMsgArrow.m_DirCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spMsgArrow.m_Dir.y) + (m_ArrowSize.x * spMsgArrow.m_DirCW.y)  }
        }
    }

    /**
    * Background
    */
    Rectangle
    {
        // common properties
        id:         rcBackground
        objectName: "rcBackground"
        x:          m_LabelPos.x
        y:          m_LabelPos.y
        width:      m_LabelSize.x
        height:     m_LabelSize.y
        color:      "transparent"

        /**
        * Handle control
        */
        TSP_HandleControl
        {
            // common properties
            id:           hcBackground
            objectName:   "hcBackground"
            anchors.fill: parent
            z:            rcBackground.activeFocus ? 0 : -1

            // advanced properties
            m_HandleVisible: rcBackground.activeFocus
            m_Target: rcBackground

            /**
            * Called when the move and size mode should be disabled
            */
            function doDisableMoveSize()
            {
                rcBackground.activeFocus = false;
            }
        }

        /**
        * Message content
        */
        Rectangle
        {
            // common properties
            id:           rcContent
            objectName:   "rcContent"
            anchors.fill: parent
            color:        "white"
            border.color: "#202020"
            border.width: 1
            radius:       3
            z:            rcBackground.activeFocus ? -1 : 0

            /**
            * Message label
            */
            Text
            {
                // common properties
                id:                  itLabel
                text:                "Message"
                anchors.fill:        parent
                anchors.margins:     2
                font.family:         "Arial"
                font.pointSize:      10
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:   Text.AlignVCenter
                wrapMode:            Text.WordWrap
                color:               "#202020"
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
                    rcBackground.forceActiveFocus();
                }
            }
        }
    }

    /**
    * Called when the from symbol changed
    */
    onM_FromChanged:
    {
        //console.log("onM_FromChanged");
        bindMsgToSrcSymbol();
    }

    /**
    * Called when the to symbol changed
    */
    onM_ToChanged:
    {
        //console.log("onM_ToChanged");
        bindMsgToDstSymbol();
    }

    /**
    * Bind message to source symbol
    */
    function bindMsgToSrcSymbol()
    {
        // from symbol should be defined
        if (!m_From)
            return;

        // unbind message from parent symbol, if previously binded
        unbindMsgFromSymbol(m_From.m_Symbol);
        m_From.m_Messages.push(this);
    }

    /**
    * Bind message to destination symbol
    */
    function bindMsgToDstSymbol()
    {
        // to symbol should be defined
        if (!m_To)
            return;

        // unbind message from parent symbol, if previously binded
        unbindMsgFromSymbol(m_To.m_Symbol);
        m_To.m_Messages.push(this);
    }

    /**
    * Unbinds a message from a symbol
    *@param symbol - symbol for which the message shoulkd be unbind
    */
    function unbindMsgFromSymbol(symbol)
    {
        if (!symbol)
            return 0;

        // remove all existing message instance from left connector
        for (var i = symbol.leftConnector.m_Messages.length - 1; i >= 0; --i)
            if (symbol.leftConnector.m_Messages[i] === this)
                symbol.leftConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from top connector
        for (var i = symbol.topConnector.m_Messages.length - 1; i >= 0; --i)
            if (symbol.topConnector.m_Messages[i] === this)
                symbol.topConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from right connector
        for (var i = symbol.rightConnector.m_Messages.length - 1; i >= 0; --i)
            if (symbol.rightConnector.m_Messages[i] === this)
                symbol.rightConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from bottom connector
        for (var i = symbol.bottomConnector.m_Messages.length - 1; i >= 0; --i)
            if (symbol.bottomConnector.m_Messages[i] === this)
                symbol.bottomConnector.m_Messages.splice(i, 1);
    }

    /**
    * Gets the start point
    *@return the start point in pixels
    */
    function getStartPoint()
    {
        // from symbol should be defined
        if (!m_From)
            return Qt.vector2d();

        return getPoint(m_From);
    }

    /**
    * Gets the end point
    *@return the end point in pixels
    */
    function getEndPoint()
    {
        // to symbol should be defined
        if (!m_To)
        {
            // message is dragging, get mouse position from start connector
            if (m_From)
                return Qt.vector2d(m_From.m_Symbol.x + m_From.connectorMouseArea.mouseX,
                                   m_From.m_Symbol.y + m_From.connectorMouseArea.mouseY);

            return Qt.vector2d();
        }

        return getPoint(m_To);
    }

    /**
    * Gets the center point
    *@return the center point on y axis in pixels
    */
    function getCenterPoint()
    {
        return Qt.vector2d(rcBackground.x + (rcBackground.width  / 2.0),
                           rcBackground.y + (rcBackground.height / 2.0));
    }

    /**
    * Gets the point centered in the connector
    *@return the point centered in the connector
    */
    function getPoint(connector)
    {
        // connector should be defined
        if (!connector)
            return Qt.vector2d();

        // get the connector parent symbol
        let symbol = connector.m_Symbol;

        // parent symbol should be defined in the connector
        if (!symbol)
            return Qt.vector2d();

        // get the connector center point
        switch (connector.m_Position)
        {
            case TSP_Connector.IEPosition.IE_P_Left:
                return Qt.vector2d(symbol.x - (connector.width              / 2) - m_Margin,
                                   symbol.y + (symbol.rectConnectors.height / 2));

            case TSP_Connector.IEPosition.IE_P_Right:
                return Qt.vector2d(symbol.x +  symbol.rectConnectors.width + (connector.width / 2) + m_Margin,
                                   symbol.y + (symbol.rectConnectors.height                   / 2));

            case TSP_Connector.IEPosition.IE_P_Top:
                return Qt.vector2d(symbol.x + (symbol.rectConnectors.width / 2), symbol.y - (connector.height / 2) - m_Margin);

            case TSP_Connector.IEPosition.IE_P_Bottom:
                return Qt.vector2d(symbol.x + (symbol.rectConnectors.width                      / 2),
                                   symbol.y +  symbol.rectConnectors.height + (connector.height / 2) + m_Margin);

            default:
                console.log("getYPos - unknown connector position - " + connector.m_Position);
                return Qt.vector2d();
        }
    }
}