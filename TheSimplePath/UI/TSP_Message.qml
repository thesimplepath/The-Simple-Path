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
    property var  m_From:       null
    property var  m_To:         null
    property int  m_Margin:     2
    property int  m_StartX:     getStartX()
    property int  m_StartY:     getStartY()
    property int  m_EndX:       getEndX()
    property int  m_EndY:       getEndY()
    property int  m_BoxWidth:   m_InvertX ? m_StartX - m_EndX : m_EndX - m_StartX
    property int  m_BoxHeight:  m_InvertY ? m_StartY - m_EndY : m_EndY - m_StartY
    property bool m_InvertX:    m_StartX  > m_EndX
    property bool m_InvertY:    m_StartY  > m_EndY
    property bool m_FromIsHorz: m_From ? (m_From.m_Position === TSP_Connector.IEPosition.IE_P_Left || m_From.m_Position === TSP_Connector.IEPosition.IE_P_Right) : false
    property bool m_ToIsHorz:   m_To   ? (m_To.m_Position   === TSP_Connector.IEPosition.IE_P_Left || m_To.m_Position   === TSP_Connector.IEPosition.IE_P_Right) : false

    // common properties
    id:     itMessage
    x:      m_InvertX                           ? m_EndX      : m_StartX
    y:      m_InvertY                           ? m_EndY      : m_StartY
    width:  m_BoxWidth  > spMessage.strokeWidth ? m_BoxWidth  : spMessage.strokeWidth
    height: m_BoxHeight > spMessage.strokeWidth ? m_BoxHeight : spMessage.strokeWidth

    /**
    * Message shape
    */
    Shape
    {
        // common properties
        id:            shMessage
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true

        /**
        * Message path
        */
        ShapePath
        {
            // common properties
            id:          spMessage
            strokeColor: "#202020"
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      itMessage.m_InvertX ? itMessage.width  : 0
            startY:      itMessage.m_InvertY ? itMessage.height : 0

            /**
            * Message curve
            */
            PathCubic
            {
                // common properties
                x:         itMessage.m_InvertX ? 0                                     : itMessage.width
                y:         itMessage.m_InvertY ? 0                                     : itMessage.height
                control1X: itMessage.m_InvertX ? (m_FromIsHorz ? 0 : itMessage.width)  : (m_FromIsHorz ? itMessage.width : 0)
                control1Y: itMessage.m_InvertY ? (m_FromIsHorz ? itMessage.height : 0) : (m_FromIsHorz ? 0 : itMessage.height)
                control2X: itMessage.m_InvertX ? (m_ToIsHorz   ? itMessage.width  : 0) : (m_ToIsHorz   ? 0 : itMessage.width)
                control2Y: itMessage.m_InvertY ? (m_ToIsHorz   ? 0 : itMessage.height) : (m_ToIsHorz   ? itMessage.height : 0)
            }
        }
    }

    /**
    * Arrow shape
    */
    Shape
    {
        // common properties
        id:            shMessageArrow
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        x:             itMessage.m_InvertX  ? -(width  / 2) + itMessage.getToConnectorMargin(true)  : itMessage.width  - (width  / 2) - itMessage.getToConnectorMargin(true)
        y:             itMessage.m_InvertY  ? -(height / 2) + itMessage.getToConnectorMargin(false) : itMessage.height - (height / 2) - itMessage.getToConnectorMargin(false)
        width:         itMessage.m_ToIsHorz ? 12 : 6
        height:        itMessage.m_ToIsHorz ? 6  : 12

        /**
        * Arrow path
        */
        ShapePath
        {
            // common properties
            id:          spMessageArrow
            strokeColor: "transparent"
            fillColor:   "#202020"
            strokeWidth: 0
            startX:      itMessage.m_InvertX ? shMessageArrow.width  : 0
            startY:      itMessage.m_InvertY ? shMessageArrow.height : 0

            /**
            * Arrow path SVG
            */
            PathSvg
            {
                // advanced properties
                property int m_FirstX:  itMessage.m_ToIsHorz ? (itMessage.m_InvertX ? shMessageArrow.width : 0)  : (itMessage.m_InvertX ? 0 : shMessageArrow.width)
                property int m_FirstY:  itMessage.m_ToIsHorz ? (itMessage.m_InvertY ? 0 : shMessageArrow.height) : (itMessage.m_InvertY ? shMessageArrow.height : 0)
                property int m_SecondX: itMessage.m_ToIsHorz ? (itMessage.m_InvertX ? 0 : shMessageArrow.width)  : shMessageArrow.width / 2
                property int m_SecondY: itMessage.m_ToIsHorz ? shMessageArrow.height / 2                         : (itMessage.m_InvertY ? 0 : shMessageArrow.height)

                path: "L " + m_FirstX + " " + m_FirstY + " L " + m_SecondX + " " + m_SecondY + " z"
            }
        }
    }

    /**
    * Background
    */
    Rectangle
    {
        // common properties
        x:            (itMessage.width / 2) - (width / 2)
        y:            itMessage.m_ToIsHorz ? (itMessage.m_InvertY ? -(height / 2) : itMessage.height - (height / 2)) : (itMessage.height / 2) - (height / 2)
        width:        100
        height:       50
        color:        "white"
        border.color: "#202020"
        border.width: 1
        radius:       3

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
    * Gets the message rect start position on x axis
    *@return the message rect start position on x axis
    */
    function getStartX()
    {
        // from symbol should be defined
        if (!m_From)
            return 0;

        return getXPos(m_From);
    }

    /**
    * Gets the message rect start position on y axis
    *@return the message rect start position on y axis
    */
    function getStartY()
    {
        // from symbol should be defined
        if (!m_From)
            return 0;

        return getYPos(m_From);
    }

    /**
    * Gets the message rect end position on x axis
    *@return the message rect end position on x axis
    */
    function getEndX()
    {
        // to symbol should be defined
        if (!m_To)
        {
            // message is dragging, get mouse position from start connector
            if (m_From)
                return m_From.m_Symbol.x + m_From.connectorMouseArea.mouseX;

            return 0;
        }

        return getXPos(m_To);
    }

    /**
    * Gets the message rect end position on y axis
    *@return the message rect end position on y axis
    */
    function getEndY()
    {
        // to symbol should be defined
        if (!m_To)
        {
            // message is dragging, get mouse position from start connector
            if (m_From)
                return m_From.m_Symbol.y + m_From.connectorMouseArea.mouseY;

            return 0;
        }

        return getYPos(m_To);
    }

    /**
    * Gets the message rect x position matching with the connector
    *@return the message rect x position matching with the connector
    */
    function getXPos(connector)
    {
        // connector should be defined
        if (!connector)
            return 0;

        // get the connector parent symbol
        let symbol = connector.m_Symbol;

        // parent symbol should be defined in the connector
        if (!symbol)
            return 0;

        // search for the connector position from which the message rect position should be measured
        switch (connector.m_Position)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   return symbol.x - (connector.width  / 2)                               - m_Margin;
            case TSP_Connector.IEPosition.IE_P_Right:  return symbol.x +  symbol.rectConnectors.width + (connector.width / 2) + m_Margin;
            case TSP_Connector.IEPosition.IE_P_Top:
            case TSP_Connector.IEPosition.IE_P_Bottom: return symbol.x + (symbol.rectConnectors.width / 2);

            default:
                console.log("getXPos - unknown connector position - " + connector.m_Position);
                return 0;
        }
    }

    /**
    * Gets the message rect y position matching with the connector
    *@return the message rect y position matching with the connector
    */
    function getYPos(connector)
    {
        // connector should be defined
        if (!connector)
            return 0;

        // get the connector parent symbol
        let symbol = connector.m_Symbol;

        // parent symbol should be defined in the connector
        if (!symbol)
            return 0;

        // search for the connector to which the message rect should end
        switch (connector.m_Position)
        {
            case TSP_Connector.IEPosition.IE_P_Left:
            case TSP_Connector.IEPosition.IE_P_Right:  return symbol.y + (symbol.rectConnectors.height / 2);
            case TSP_Connector.IEPosition.IE_P_Top:    return symbol.y - (connector.height             / 2)                     - m_Margin;
            case TSP_Connector.IEPosition.IE_P_Bottom: return symbol.y +  symbol.rectConnectors.height + (connector.height / 2) + m_Margin;

            default:
                console.log("getYPos - unknown connector position - " + connector.m_Position);
                return 0;
        }
    }

    /**
    * Gets the margin to apply to where the message is attached to
    *@param onXAxis [bool] - if true, the margin will be get for the x axis, otherwise for the y axis
    *@return the to connector margin to apply
    */
    function getToConnectorMargin(onXAxis)
    {
        if (!m_To)
            return 0;

        // search for the connector to which the message rect should end
        switch (m_To.m_Position)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   return onXAxis ?     (m_To.width  / 2) - m_Margin : 0;
            case TSP_Connector.IEPosition.IE_P_Right:  return onXAxis ?     (m_To.width  / 2) + m_Margin : 0;
            case TSP_Connector.IEPosition.IE_P_Top:    return onXAxis ? 0 : (m_To.height / 2) - m_Margin;
            case TSP_Connector.IEPosition.IE_P_Bottom: return onXAxis ? 0 : (m_To.height / 2) + m_Margin;

            default:
                console.log("getToConnectorMargin - unknown \"to\" connector - " + m_To.m_Position);
                return 0;
        }
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
}
