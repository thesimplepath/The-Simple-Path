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
    property int  m_FromConn:   TSP_Connector.IEPosition.IE_P_None
    property int  m_ToConn:     TSP_Connector.IEPosition.IE_P_None
    property int  m_StartX:     getStartX()
    property int  m_StartY:     getStartY()
    property int  m_EndX:       getEndX()
    property int  m_EndY:       getEndY()
    property int  m_BoxWidth:   m_InvertX ? m_StartX - m_EndX : m_EndX - m_StartX
    property int  m_BoxHeight:  m_InvertY ? m_StartY - m_EndY : m_EndY - m_StartY
    property bool m_InvertX:    m_StartX  > m_EndX
    property bool m_InvertY:    m_StartY  > m_EndY
    property bool m_FromIsHorz: m_FromConn === TSP_Connector.IEPosition.IE_P_Left || m_FromConn === TSP_Connector.IEPosition.IE_P_Right
    property bool m_ToIsHorz:   m_ToConn   === TSP_Connector.IEPosition.IE_P_Left || m_ToConn   === TSP_Connector.IEPosition.IE_P_Right

    // common properties
    id:     itMessage
    x:      m_InvertX   ? m_EndX : m_StartX
    y:      m_InvertY   ? m_EndY : m_StartY
    width:  m_BoxWidth  > spMessage.strokeWidth ? m_BoxWidth  : spMessage.strokeWidth
    height: m_BoxHeight > spMessage.strokeWidth ? m_BoxHeight : spMessage.strokeWidth

    /**
    * Message shape
    */
    Shape
    {
        // common properties
        id: shMessage
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 8
        smooth: true

        /**
        * Message path
        */
        ShapePath
        {
            // common properties
            id: spMessage
            strokeColor: "black"
            fillColor: "transparent"
            strokeWidth: 1
            startX: itMessage.m_InvertX ? itMessage.width  : 0
            startY: itMessage.m_InvertY ? itMessage.height : 0

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
    * Called when the from symbol changed
    */
    onM_FromChanged:
    {
        // from symbol should be defined
        if (!m_From)
            return;

        // remove all existing message instance from left connector
        for (var i = m_From.leftConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_From.leftConnector.m_Messages[i] === this)
                m_From.leftConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from top connector
        for (var i = m_From.topConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_From.topConnector.m_Messages[i] === this)
                m_From.topConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from right connector
        for (var i = m_From.rightConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_From.rightConnector.m_Messages[i] === this)
                m_From.rightConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from bottom connector
        for (var i = m_From.bottomConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_From.bottomConnector.m_Messages[i] === this)
                m_From.bottomConnector.m_Messages.splice(i, 1);

        // search for the connector on which the message is attached on the from symbol
        switch (m_FromConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   m_From.leftConnector.m_Messages.push  (this); break;
            case TSP_Connector.IEPosition.IE_P_Right:  m_From.rightConnector.m_Messages.push (this); break;
            case TSP_Connector.IEPosition.IE_P_Top:    m_From.topConnector.m_Messages.push   (this); break;
            case TSP_Connector.IEPosition.IE_P_Bottom: m_From.bottomConnector.m_Messages.push(this); break;
        }
    }

    /**
    * Called when the to symbol changed
    */
    onM_ToChanged:
    {
        // to symbol should be defined
        if (!m_To)
            return;

        // remove all existing message instance from left connector
        for (var i = m_To.leftConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_To.leftConnector.m_Messages[i] === this)
                m_To.leftConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from top connector
        for (var i = m_To.topConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_To.topConnector.m_Messages[i] === this)
                m_To.topConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from right connector
        for (var i = m_To.rightConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_To.rightConnector.m_Messages[i] === this)
                m_To.rightConnector.m_Messages.splice(i, 1);

        // remove all existing message instance from bottom connector
        for (var i = v.bottomConnector.m_Messages.length - 1; i >= 0; --i)
            if (m_To.bottomConnector.m_Messages[i] === this)
                m_To.bottomConnector.m_Messages.splice(i, 1);

        // search for the connector on which the message is attached on the from symbol
        switch (m_FromConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   m_To.leftConnector.m_Messages.push  (this); break;
            case TSP_Connector.IEPosition.IE_P_Right:  m_To.rightConnector.m_Messages.push (this); break;
            case TSP_Connector.IEPosition.IE_P_Top:    m_To.topConnector.m_Messages.push   (this); break;
            case TSP_Connector.IEPosition.IE_P_Bottom: m_To.bottomConnector.m_Messages.push(this); break;
        }
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

        // search for the connector from which the message rect should start
        switch (m_FromConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   return m_From.x - (m_From.leftConnector.width  / 2) - 2;
            case TSP_Connector.IEPosition.IE_P_Right:  return m_From.x +  m_From.rectConnectors.width + (m_From.rightConnector.width / 2) + 2;
            case TSP_Connector.IEPosition.IE_P_Top:
            case TSP_Connector.IEPosition.IE_P_Bottom: return m_From.x + (m_From.rectConnectors.width / 2);

            default:
                console.log("getStartX - unknown \"from\" connector - " + m_FromConn);
                return 0;
        }
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

        // search for the connector from which the message rect should start
        switch (m_FromConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:
            case TSP_Connector.IEPosition.IE_P_Right:  return m_From.y + (m_From.rectConnectors.height / 2);
            case TSP_Connector.IEPosition.IE_P_Top:    return m_From.y - (m_From.topConnector.height   / 2) - 2;
            case TSP_Connector.IEPosition.IE_P_Bottom: return m_From.y +  m_From.rectConnectors.height + (m_From.bottomConnector.height / 2) + 2;

            default:
                console.log("getStartY - unknown \"from\" connector - " + m_FromConn);
                return 0;
        }
    }

    /**
    * Gets the message rect end position on x axis
    *@return the message rect end position on x axis
    */
    function getEndX()
    {
        // to symbol should be defined
        if (!m_To)
            return 0;

        // search for the connector to which the message rect should end
        switch (m_ToConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:   return m_To.x - (m_To.leftConnector.width  / 2) - 2;
            case TSP_Connector.IEPosition.IE_P_Right:  return m_To.x +  m_To.rectConnectors.width + (m_To.rightConnector.width / 2) + 2;
            case TSP_Connector.IEPosition.IE_P_Top:
            case TSP_Connector.IEPosition.IE_P_Bottom: return m_To.x + (m_To.rectConnectors.width / 2);

            default:
                console.log("getEndX - unknown \"to\" connector - " + m_ToConn);
                return 0;
        }
    }

    /**
    * Gets the message rect end position on y axis
    *@return the message rect end position on y axis
    */
    function getEndY()
    {
        // to symbol should be defined
        if (!m_To)
            return 0;

        // search for the connector to which the message rect should end
        switch (m_ToConn)
        {
            case TSP_Connector.IEPosition.IE_P_Left:
            case TSP_Connector.IEPosition.IE_P_Right:  return m_To.y + (m_To.rectConnectors.height / 2);
            case TSP_Connector.IEPosition.IE_P_Top:    return m_To.y - (m_To.topConnector.height   / 2) - 2;
            case TSP_Connector.IEPosition.IE_P_Bottom: return m_To.y +  m_To.rectConnectors.height + (m_To.bottomConnector.height / 2) + 2;

            default:
                console.log("getEndY - unknown \"to\" connector - " + m_ToConn);
                return 0;
        }
    }
}
