import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

ApplicationWindow
{
    // advanced properties
    property ApplicationWindow m_MainWindow: wiMainWnd

    // common properties
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
    }

    /*REM
    ScrollView {
        width: 200
        height: 200
        clip: true

        Label {
            text: "ABC"
            font.pixelSize: 224
        }
    }
    */
    /*REM
    Rectangle {
        id: frame
        clip: true
        width: 160
        height: 160
        border.color: "black"
        anchors.centerIn: parent

        Text {
            id: content
            text: "ABC"
            font.pixelSize: 160
            x: -hbar.position * width
            y: -vbar.position * height
        }

        ScrollBar {
            id: vbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Vertical
            size: frame.height / content.height
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }

        ScrollBar {
            id: hbar
            hoverEnabled: true
            active: hovered || pressed
            orientation: Qt.Horizontal
            size: frame.width / content.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }
    */
}
