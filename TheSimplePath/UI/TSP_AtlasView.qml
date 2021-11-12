import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Atlas view
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_Atlas: ctAtlasView
    property var m_Model: null

    // common properties
    id: ctAtlasView
    objectName: "ctAtlasView"
    anchors.fill: parent

    /**
    * Models stack view
    */
    StackView
    {
        // common properties
        id: svAtlasView
        objectName: "svAtlasView"
        anchors.fill: parent
        initialItem: cpPageItem
    }

    Component
    {
        id: cpPageItem

        TSP_PageView
        {}
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
