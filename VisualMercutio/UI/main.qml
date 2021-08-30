import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

Window {
    visible: true
    width: 800
    height: 600
    // todo FIXME -cFeature -oJean: Change the name when it will be decided
    title: qsTr("Visual Mercutio");

    Rectangle
    {
        property real m_FirstLinePos:   height      / 3
        property real m_SecondLinePos: (height * 2) / 3

        id: processSymbol
        x: 50
        y: 50
        width: 100
        height: 80
        color: "white"
        border.color: "black"
        border.width: 1
        radius: 3

        TextInput
        {
            x: 0
            y: 0
            width: processSymbol.width
            height: processSymbol.m_FirstLinePos
        }

        Shape
        {
            id: topLine
            width: processSymbol.width
            height: processSymbol.height

            ShapePath
            {
                fillColor: "transparent"
                strokeColor: "black"
                strokeWidth: 1

                startX: 1
                startY: processSymbol.m_FirstLinePos

                PathLine { x: 100; y: processSymbol.m_FirstLinePos }
            }
        }

        Shape
        {
            id: bottomLine
            width: processSymbol.width
            height: processSymbol.height

            ShapePath
            {
                fillColor: "transparent"
                strokeColor: "black"
                strokeWidth: 1

                startX: 1
                startY: processSymbol.m_SecondLinePos

                PathLine { x: processSymbol.width; y: processSymbol.m_SecondLinePos }
            }
        }
    }
}
