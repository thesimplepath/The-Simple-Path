import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Box, it's a basic component which can be moved and resized, and contain connectors
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias nameLabel:       txName
    property alias rectConnectors:  rcConnectors
    property alias leftConnector:   coLeft
    property alias topConnector:    coTop
    property alias rightConnector:  coRight
    property alias bottomConnector: coBottom

    // advanced properties
    property var m_PageContent: parent

    // common properties
    id: ctBox
    objectName: "ctBox"

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
            m_Box:      rcConnectors.parent
            m_Position: TSP_Connector.IEPosition.IE_P_Left
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
            m_Box:      rcConnectors.parent
            m_Position: TSP_Connector.IEPosition.IE_P_Top
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
            m_Box:      rcConnectors.parent
            m_Position: TSP_Connector.IEPosition.IE_P_Right
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
            m_Box:      rcConnectors.parent
            m_Position: TSP_Connector.IEPosition.IE_P_Bottom
        }
    }

    /**
    * Symbol background, also handles gesture
    */
    TSP_HandleControl
    {
        // common properties
        id: hcBackground
        objectName: "hcBackground"
        anchors.fill: parent
        z: ctBox.activeFocus ? 0 : -1

        // advanced properties
        m_HandleVisible: ctBox.activeFocus
        m_Target: ctBox

        /**
        * Called when the move and size mode should be disabled
        */
        function doDisableMoveSize()
        {}
    }

    /**
    * Symbol content
    */
    Rectangle
    {
        // common properties
        id: rcContent
        objectName: "rcContent"
        anchors.fill: parent
        color: "white"
        radius: 3
        anchors.margins: 1
        z: ctBox.activeFocus ? -1 : 0
        clip: true

        /**
        * Top label
        */
        Text
        {
            // common properties
            id: txName
            objectName: "txName"
            text: "<b>Hello World!</b>"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            font.family: "Arial"
            font.pointSize: 12
            wrapMode: Text.WordWrap
            color: "#202020"
            clip: true
        }

        /**
        * Middle label
        */
        Text
        {
            // common properties
            id: txObjNb
            objectName: "txObjNb"
            text: "ID: 1234"
            anchors.left: parent.left
            anchors.top: txName.bottom
            anchors.right: parent.right
            font.family: "Arial"
            font.pointSize: 10
            wrapMode: Text.WordWrap
            color: "#202020"
            clip: true
        }

        /**
        * Bottom label
        */
        Text
        {
            // common properties
            id: txTeamName
            objectName: "txTeamName"
            text: "Team: Alpha"
            anchors.left: parent.left
            anchors.top: txObjNb.bottom
            anchors.right: parent.right
            font.family: "Arial"
            font.pointSize: 10
            wrapMode: Text.WordWrap
            color: "#202020"
            clip: true
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
}
