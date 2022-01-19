import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Activity symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    // common properties
    m_Radius:      5
    m_BorderWidth: 2

    /// called when activity should be resized
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
