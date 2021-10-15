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
                y: 200
                width: 100
                height: 80
            }

            TSP_ProcedureSymbol
            {
                id: symbol3
                x: 400
                y: 200
                width: 100
                height: 80
            }

            Item
            {
                property int  startX:    symbol1.x + (symbol1.rectConnectors.width / 2)
                property int  startY:    symbol1.y +  symbol1.rectConnectors.height + (symbol1.bottomConnector.height / 2) + 2
                property int  endX:      symbol2.x + (symbol2.rectConnectors.width / 2)
                property int  endY:      symbol2.y - (symbol2.topConnector.height  / 2) - 2
                property int  boxWidth:  invertX ? startX - endX : endX - startX
                property int  boxHeight: invertY ? startY - endY : endY - startY
                property bool invertX:   startX > endX
                property bool invertY:   startY > endY

                id:     itLink
                x:      invertX ? endX : startX
                y:      invertY ? endY : startY
                width:  boxWidth  > spLink.strokeWidth ? boxWidth  : spLink.strokeWidth
                height: boxHeight > spLink.strokeWidth ? boxHeight : spLink.strokeWidth

                Shape
                {
                    id: shLink
                    anchors.fill: parent
                    layer.enabled: true
                    layer.samples: 8
                    smooth: true

                    ShapePath
                    {
                        id: spLink
                        strokeColor: "black"
                        fillColor: "transparent"
                        strokeWidth: 1
                        startX: itLink.invertX ? itLink.width  : 0
                        startY: itLink.invertY ? itLink.height : 0

                        PathCubic
                        {
                            x:         itLink.invertX ? 0             : itLink.width
                            y:         itLink.invertY ? 0             : itLink.height
                            control1X: itLink.invertX ? itLink.width  : 0
                            control1Y: itLink.invertY ? 0             : itLink.height
                            control2X: itLink.invertX ? 0             : itLink.width
                            control2Y: itLink.invertY ? itLink.height : 0
                        }
                    }
                }
            }

            Item
            {
                property int  startX:    symbol1.x + (symbol1.rectConnectors.width / 2)
                property int  startY:    symbol1.y +  symbol1.rectConnectors.height + (symbol1.bottomConnector.height / 2) + 2
                property int  endX:      symbol3.x + (symbol3.rectConnectors.width / 2)
                property int  endY:      symbol3.y - (symbol3.topConnector.height / 2) - 2
                property int  boxWidth:  invertX ? startX - endX : endX - startX
                property int  boxHeight: invertY ? startY - endY : endY - startY
                property bool invertX:   startX > endX
                property bool invertY:   startY > endY

                id:     itLink2
                x:      invertX ? endX : startX
                y:      invertY ? endY : startY
                width:  boxWidth  > spLink2.strokeWidth ? boxWidth  : spLink2.strokeWidth
                height: boxHeight > spLink2.strokeWidth ? boxHeight : spLink2.strokeWidth

                Shape
                {
                    id: shLink2
                    anchors.fill: parent
                    layer.enabled: true
                    layer.samples: 8
                    smooth: true

                    ShapePath
                    {
                        id: spLink2
                        strokeColor: "black"
                        fillColor: "transparent"
                        strokeWidth: 1
                        startX: itLink2.invertX ? itLink2.width  : 0
                        startY: itLink2.invertY ? itLink2.height : 0

                        PathCubic
                        {
                            x:         itLink2.invertX ? 0             : itLink2.width
                            y:         itLink2.invertY ? 0             : itLink2.height
                            control1X: itLink2.invertX ? itLink2.width  : 0
                            control1Y: itLink2.invertY ? 0             : itLink2.height
                            control2X: itLink2.invertX ? 0             : itLink2.width
                            control2Y: itLink2.invertY ? itLink2.height : 0
                        }
                    }
                }
            }
        }
    }
    /**/
}
