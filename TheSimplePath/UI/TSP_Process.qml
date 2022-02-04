import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Start symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    // common properties
    m_Color:       "#202020"
    m_BgColor:     "#009ed6"
    m_TextColor:   Styles.m_LightTextColor
    m_Radius:      10
    m_BorderWidth: 2

    // child components
    titleText.anchors.bottom:      rectContents.bottom
    titleText.horizontalAlignment: Text.AlignHCenter
    titleText.verticalAlignment:   Text.AlignVCenter
    descriptionText.visible:       false
    commentsText.visible:          false

    /// called when process should be resized
    onResize: function(direction, deltaX, deltaY)
    {
        const connectorWidth  = 14;
        const connectorHeight = 14;

        // update connectors positions
        leftConnector.x   =  -((connectorWidth  / 2) + 2);
        topConnector.y    =  -((connectorHeight / 2) + 2);
        rightConnector.x  =   width  + 2 - (connectorWidth  / 2);
        bottomConnector.y =   height + 2 - (connectorHeight / 2);
    }
}
