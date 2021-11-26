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
    m_Color:       "#202020"
    m_BgColor:     "#009ed6"
    m_TextColor:   "white"
    m_Radius:      10
    m_BorderWidth: 2

    // child components
    titleText.anchors.bottom:      rectContents.bottom
    titleText.horizontalAlignment: Text.AlignHCenter
    titleText.verticalAlignment:   Text.AlignVCenter
    descriptionText.visible:       false
    commentsText.visible:          false
}
