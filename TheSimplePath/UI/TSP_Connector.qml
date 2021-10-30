import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Connector, used to connect two symbols with a message
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Connector position
    */
    enum IEPosition
    {
        IE_P_None,
        IE_P_Left,
        IE_P_Top,
        IE_P_Right,
        IE_P_Bottom
    }

    // aliases
    property alias connectorRect:      rcConnector
    property alias connectorMouseArea: maConnector

    // advanced properties
    property var m_Document: null
    property var m_Symbol:   null
    property var m_Messages: []
    property int m_Position: IEPosition.IE_P_None

    // common properties
    id: ctConnector
    objectName: "ctConnector"
    width: 14
    height: 14

    /**
    * Connector rectangle
    */
    Rectangle
    {
        // common properties
        id: rcConnector
        objectName: "rcConnector"
        anchors.fill: parent
        color: "transparent"
        border.color: "#c0c0c0"
        border.width: 3
        radius: 7
    }

    /**
    * Connector mouse area
    */
    MouseArea
    {
        property bool m_IsDragging: false

        // common properties
        id: maConnector
        objectName: "maConnector"
        anchors.fill: parent
        cursorShape: Qt.CrossCursor
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        onPressed: function(mouseEvent)
        {
            //REM console.log("DRAG START - " + mouseEvent.x + " - " + mouseEvent.y);
            m_IsDragging = true;

            if (m_Document)
                m_Document.addMessage(ctConnector, null);
        }

        onReleased: function(mouseEvent)
        {
            //REM console.log("DRAG END - " + mouseEvent.x + " - " + mouseEvent.y);
            m_IsDragging = false;
        }

        onPositionChanged: function(mouseEvent)
        {
            if (!m_IsDragging)
                return;

            //REM console.log("DRAG MOVE - " + mouseEvent.x + " - " + mouseEvent.y);
        }
    }
}
