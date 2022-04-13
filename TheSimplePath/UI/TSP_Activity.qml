import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Activity symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    // common properties
    m_Radius:      Styles.m_ActivityRadius
    m_BorderWidth: Styles.m_ActivityBorderWidth

    /// called when activity should be resized
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
