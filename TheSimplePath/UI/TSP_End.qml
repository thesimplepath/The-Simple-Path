import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Start symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    m_Color:       Styles.m_EndBorderColor
    m_BgColor:     Styles.m_EndBgColor
    m_Radius:      Styles.m_EndRadius
    m_BorderWidth: Styles.m_EndBorderWidth

    /// called when end symbol should be resized
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
