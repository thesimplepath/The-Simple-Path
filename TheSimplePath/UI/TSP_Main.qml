import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

Window
{
    visible: true
    width: 800
    height: 600
    title: qsTr("The Simple Path")

    Rectangle
    {
        id: rcToolbox
        objectName: "rcToolbox"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 40

        Button
        {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: 75
            text: "Add Procedure"
        }
    }

    TSP_DocumentView
    {
        id: dvDocumentView
        objectName: "dvDocumentView"
        anchors.left: parent.left
        anchors.top: rcToolbox.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    /*REM*/
    Rectangle
    {
        anchors.fill: parent

        MouseArea
        {
            property var m_Target: parent

            anchors.fill: parent
            hoverEnabled: true

            onPressed: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.forceActiveFocus(true);
            }

            TSP_ProcedureSymbol
            {
                id: symbol1
                x: 50
                y: 50
                width: 100
                height: 80
            }

            TSP_ProcedureSymbol
            {
                id: symbol2
                x: 200
                y: 400
                width: 100
                height: 80
            }

            TSP_ProcedureSymbol
            {
                id: symbol3
                x: 400
                y: 150
                width: 100
                height: 80
            }

            TSP_Message
            {
                id: message1
                m_From: symbol1
                m_To: symbol2
                m_FromConn: TSP_Connector.IEPosition.IE_P_Bottom
                m_ToConn: TSP_Connector.IEPosition.IE_P_Top
            }

            TSP_Message
            {
                id: message2
                m_From: symbol1
                m_To: symbol3
                m_FromConn: TSP_Connector.IEPosition.IE_P_Bottom
                m_ToConn: TSP_Connector.IEPosition.IE_P_Left
            }
        }
    }
    /**/
}
