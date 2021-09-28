import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

Window
{
    visible: true
    width: 800
    height: 600
    // todo FIXME -cFeature -oJean: Change the name when it will be decided
    title: qsTr("Visual Mercutio");

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

            RPM_ProcedureSymbol
            {
                x: 50
                y: 50
                width: 100
                height: 80
            }
        }
    }
}
