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
    // common properties
    m_Radius:      0
    m_BorderWidth: 3

    // child components
    titleText.anchors.bottom:      rectContents.bottom
    titleText.horizontalAlignment: Text.AlignHCenter
    titleText.verticalAlignment:   Text.AlignVCenter
    descriptionText.visible:       false
    commentsText.visible:          false
}
