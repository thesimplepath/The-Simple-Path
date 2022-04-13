pragma Singleton

import QtQuick 2.15

/**
* Qml common style properties
*@author Jean-Milost Reymond
*/
QtObject
{
    // glyphs properties
    readonly property string m_PageBreakGlyph:        "qrc:/Resources/Images/PageBreak_Logo_Normal.svg"
    readonly property string m_ProcessPageBreakGlyph: "qrc:/Resources/Images/PageBreak_Logo_Process.svg"
    readonly property string m_PageItemGlyph:         "qrc:/Resources/Images/Page.svg"

    // color properties
    readonly property string m_WindowBgColor:            "#808080"
    readonly property string m_DocumentBgColor:          "white"
    readonly property string m_ProcessFillColor:         "#009ed6"
    readonly property string m_ProcessOutlineColor:      "#202020"
    readonly property string m_DarkTextColor:            "#202020"
    readonly property string m_LightTextColor:           "white"
    readonly property string m_HighlightColor:           "#4e8cde"
    readonly property string m_HandleBgColor:            "#c0c0c0"
    readonly property string m_HandleBorderColor:        "black"
    readonly property string m_HandleControlBorderColor: "#202020"
    readonly property string m_ConnectorBgColor:         "white"
    readonly property string m_ConnectorBorderColor:     "#c0c0c0"
    readonly property string m_BoxHandleBgColor:         "#c0c0c0"
    readonly property string m_BoxHandleBorderColor:     "black"
    readonly property string m_BoxBgColor:               "white"
    readonly property string m_BoxBorderColor:           "#202020"
    readonly property string m_LinkBgColor:              "white"
    readonly property string m_LinkBorderColor:          "#202020"
    readonly property string m_ProcessPageBreakBgColor:  "#009ed6"
    readonly property string m_StartBgColor:             "white"
    readonly property string m_StartBorderColor:         "#00b050"
    readonly property string m_EndBgColor:               "white"
    readonly property string m_EndBorderColor:           "red"
    readonly property string m_PageBreakBgColor:         "white"
    readonly property string m_PageBreakBorderColor:     "#202020"
    readonly property string m_MessageBgColor:           "white"
    readonly property string m_MessageBorderColor:       "#cc0099"
    readonly property string m_PageListHeaderBgColor:    "#f0f0f0"

    // skinning properties
    readonly property int m_WindowWidth:                800
    readonly property int m_WindowHeight:               600
    readonly property int m_HandleWidth:                7
    readonly property int m_HandleHeight:               7
    readonly property int m_HandleBorderWidth:          1
    readonly property int m_HandleRadius:               3
    readonly property int m_ConnectorWidth:             14
    readonly property int m_ConnectorHeight:            14
    readonly property int m_ConnectorBorderWidth:       3
    readonly property int m_ConnectorRadius:            7
    readonly property int m_BoxBorderWidth:             1
    readonly property int m_BoxRadius:                  3
    readonly property int m_BoxTextMargin:              2
    readonly property int m_ProcessRadius:              10
    readonly property int m_ProcessBorderWidth:         2
    readonly property int m_ActivityRadius:             5
    readonly property int m_ActivityBorderWidth:        2
    readonly property int m_StartRadius:                0
    readonly property int m_StartBorderWidth:           2
    readonly property int m_EndRadius:                  0
    readonly property int m_EndBorderWidth:             2
    readonly property int m_PageBreakRadius:            0
    readonly property int m_PageBreakBorderWidth:       2
    readonly property int m_LinkBorderWidth:            1
    readonly property int m_LinkRadius:                 3
    readonly property int m_LinkTextMargin:             2
    readonly property int m_PageListWidth:              150
    readonly property int m_PageListHeaderHeight:       26
    readonly property int m_PageListHeaderButtonRadius: 3
    readonly property int m_PageItemHeight:             25
    readonly property int m_PageItemTextMargin:         5

    // component font properties
    readonly property QtObject m_ComponentFont: QtObject
    {
        readonly property string m_Family: "Arial"
        readonly property int    m_Size:   9
    }

    // page list item font properties
    readonly property QtObject m_PageItemFont: QtObject
    {
        readonly property string m_Family: "Arial"
        readonly property int    m_Size:   9
    }
}
