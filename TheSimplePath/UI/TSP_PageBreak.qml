import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Page break symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    // advanced properties
    property string m_NormalURL:  Styles.m_PageBreakGlyph
    property string m_ProcessURL: Styles.m_ProcessPageBreakGlyph
    property bool   m_IsProcess:  false
    property bool   m_IsExit:     false

    // common properties
    m_Color:       Styles.m_PageBreakBorderColor
    m_BgColor:     m_IsProcess ? Styles.m_ProcessPageBreakBgColor : Styles.m_PageBreakBgColor
    m_TextColor:   m_IsProcess ? Styles.m_LightTextColor          : Styles.m_DarkTextColor
    m_Radius:      Styles.m_PageBreakRadius
    m_BorderWidth: Styles.m_PageBreakBorderWidth

    // child components
    titleText.anchors.bottom:      rectContents.bottom
    titleText.horizontalAlignment: Text.AlignHCenter
    titleText.verticalAlignment:   Text.AlignVCenter
    descriptionText.visible:       false
    commentsText.visible:          false

    /**
    * Top glyph
    */
    Image
    {
        id: imTopGlyph
        objectName: "imTopGlyph"
        source: m_IsProcess ? m_ProcessURL : m_NormalURL
        sourceSize.width: width
        sourceSize.height:height
        x: -(width  / 2) + 6
        y: -(height / 2) + 2
        width: 60
        height: 50
        fillMode: Image.PreserveAspectFit
        visible: m_IsExit
    }

    /**
    * Bottom glyph
    */
    Image
    {
        id: imBottomGlyph
        objectName: "imBottomGlyph"
        source: m_IsProcess ? m_ProcessURL : m_NormalURL
        sourceSize.width: width
        sourceSize.height:height
        x: parent.width  - (width  / 2) - 6
        y: parent.height - (height / 2) - 2
        width: 60
        height: 50
        fillMode: Image.PreserveAspectFit
        visible: !m_IsExit
    }

    /// called when page break should be resized
    onResize: function(direction, deltaX, deltaY)
    {
        const connectorWidth  = Styles.m_ConnectorWidth;
        const connectorHeight = Styles.m_ConnectorHeight;

        // update connectors positions
        leftConnector.x   =  -((connectorWidth  / 2) + 2);
        topConnector.y    =  -((connectorHeight / 2) + 2);
        rightConnector.x  =   width  + 2 - (connectorWidth  / 2);
        bottomConnector.y =   height + 2 - (connectorHeight / 2);
    }
}
