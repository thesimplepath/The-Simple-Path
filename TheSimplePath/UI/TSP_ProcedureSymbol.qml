import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Procedure symbol
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias rectConnectors:  rcConnectors
    property alias leftConnector:   coLeft
    property alias topConnector:    coTop
    property alias rightConnector:  coRight
    property alias bottomConnector: coBottom

    // common properties
    id: hcProcedureSymbol

    /**
    * Connectors
    */
    Rectangle
    {
        // common properties
        id: rcConnectors
        anchors.fill: parent
        color: "transparent"

        /**
        * Left connector
        */
        TSP_Connector
        {
            // common properties
            id: coLeft
            x:   parent.x - (width + 2)
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: true
        }

        /**
        * Top connector
        */
        TSP_Connector
        {
            // common properties
            id: coTop
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:   parent.y - (height + 2)
            visible: true
        }

        /**
        * Right connector
        */
        TSP_Connector
        {
            // common properties
            id: coRight
            x:   parent.x + parent.width + 2
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: true
        }

        /**
        * Bottom connector
        */
        TSP_Connector
        {
            // common properties
            id: coBottom
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:   parent.y + parent.height + 2
            visible: true
        }
    }

    /**
    * Symbol background, also handles gesture
    */
    TSP_HandleControl
    {
        // common properties
        id: hcBackground
        anchors.fill: parent
        z: hcProcedureSymbol.activeFocus ? 0 : -1

        // advanced properties
        m_HandleVisible: hcProcedureSymbol.activeFocus
        m_Target: hcProcedureSymbol

        /**
        * Called when the move and size mode should be disabled
        */
        function doDisableMoveSize()
        {
            hcProcedureSymbol.activeFocus = false;
        }
    }

    /**
    * Symbol content
    */
    Rectangle
    {
        // common properties
        id: rcContent
        anchors.fill: parent
        color: "transparent"
        border.color: "#202020"
        border.width: 1
        radius: 3
        z: hcProcedureSymbol.activeFocus ? -1 : 0
        clip: true

        Text
        {
            id: txName
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

        Text
        {
            id: txObjNb
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

        Text
        {
            id: txTeamName
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
            anchors.fill: parent

            /// called when the view is clicked
            onClicked:
            {
                //REM setMode(TSP_ProcedureSymbol.IEMode.IE_M_MoveSize);
                hcProcedureSymbol.forceActiveFocus();
            }
        }
    }
}
