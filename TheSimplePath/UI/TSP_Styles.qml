pragma Singleton

import QtQuick 2.15

/**
* Qml common style properties
*@author Jean-Milost Reymond
*/
QtObject
{
    // color properties
    readonly property string m_ProcessFillColor:    "#009ed6"
    readonly property string m_ProcessOutlineColor: "#202020"
    readonly property string m_DarkTextColor:       "#202020"
    readonly property string m_LightTextColor:      "white"
    readonly property string m_HighlightColor:      "#4e8cde"

    // font properties
    readonly property string m_FontFamily: "Arial"

    // skinning properties
    readonly property int m_ProcessRadius:       10
    readonly property int m_ProcessOutlineWidth: 2
    readonly property int m_ConnectorWidth:      14
    readonly property int m_ConnectorHeight:     14
}
