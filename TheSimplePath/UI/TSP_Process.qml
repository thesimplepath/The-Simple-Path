import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Start symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    // common properties
    m_Color:       Styles.m_ProcessOutlineColor
    m_BgColor:     Styles.m_ProcessFillColor
    m_TextColor:   Styles.m_LightTextColor
    m_Radius:      Styles.m_ProcessRadius
    m_BorderWidth: Styles.m_ProcessOutlineWidth

    // child components
    titleText.anchors.bottom:      rectContents.bottom
    titleText.horizontalAlignment: Text.AlignHCenter
    titleText.verticalAlignment:   Text.AlignVCenter
    descriptionText.visible:       false
    commentsText.visible:          false

    /// called when process should be resized
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
