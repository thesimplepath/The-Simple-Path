import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

Window
{
    id: wiMainWnd
    objectName: "wiMainWnd"
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
            id: btAddProc
            objectName: "btAddProc"
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

        m_Parent: rcPage
    }

    /*REM*/
    Rectangle
    {
        id:           rcPage
        objectName:   "rcPage"
        anchors.fill: parent

        MouseArea
        {
            property var m_Target: parent

            id: maPage
            objectName: "maPage"
            anchors.fill: parent
            hoverEnabled: true

            onPressed: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.forceActiveFocus(true);
            }
        }

        /*REM*/
        TSP_Box
        {
            id: symbol1
            objectName: "symbol1"
            x: 50
            y: 50
            width: 100
            height: 80

            m_Document: dvDocumentView

            //nameLabel.text: "1"
        }

        TSP_Box
        {
            id: symbol2
            objectName: "symbol2"
            x: 200
            y: 400
            width: 100
            height: 80

            m_Document: dvDocumentView

            //nameLabel.text: "2"
        }

        TSP_Box
        {
            id: symbol3
            objectName: "symbol3"
            x: 400
            y: 150
            width: 100
            height: 80

            m_Document: dvDocumentView

            //nameLabel.text: "3"
        }
        /**/

        /*REM*/
        TSP_Message
        {
            id: message1
            objectName: "message1"
            m_From: symbol1.bottomConnector
            m_To: symbol2.topConnector
        }

        TSP_Message
        {
            id: message2
            objectName: "message2"
            m_From: symbol1.bottomConnector
            m_To: symbol3.leftConnector
        }
        /**/
    }
    /**/
}
