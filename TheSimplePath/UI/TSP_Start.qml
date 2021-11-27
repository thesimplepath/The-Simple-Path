import QtQuick 2.15
import QtQuick.Controls 2.15

// custom qt component
import "Component"

/**
* Start symbol
*@author Jean-Milost Reymond
*/
TSP_Box
{
    m_Color:       "#00b050"
    m_BgColor:     "white"
    m_Radius:      0
    m_BorderWidth: 2

    /// called when start symbol should be resized
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
