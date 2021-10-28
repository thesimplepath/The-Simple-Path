import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Application model item
*@author Jean-Milost Reymond
*/
T.Item
{
    // global properties
    property var m_Model: null

    Rectangle
    {
        anchors.fill: parent
        color: "#ff0000"
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        target: m_Model
    }
}
