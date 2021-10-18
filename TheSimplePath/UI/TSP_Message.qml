import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Templates 2.15 as T

/**
* Message, it's a link between 2 symbols
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var  m_From:      null
    property var  m_To:        null
    property int  m_StartX:    m_From.x  + (m_From.rectConnectors.width  / 2)
    property int  m_StartY:    m_From.y  +  m_From.rectConnectors.height + (m_From.bottomConnector.height / 2) + 2
    property int  m_EndX:      m_To.x    + (m_To.rectConnectors.width    / 2)
    property int  m_EndY:      m_To.y    - (m_To.topConnector.height     / 2) - 2
    property int  m_BoxWidth:  m_InvertX ? m_StartX - m_EndX : m_EndX - m_StartX
    property int  m_BoxHeight: m_InvertY ? m_StartY - m_EndY : m_EndY - m_StartY
    property bool m_InvertX:   m_StartX  > m_EndX
    property bool m_InvertY:   m_StartY  > m_EndY

    // common properties
    id:     itMessage
    x:      m_InvertX   ? m_EndX : m_StartX
    y:      m_InvertY   ? m_EndY : m_StartY
    width:  m_BoxWidth  > spMessage.strokeWidth ? m_BoxWidth  : spMessage.strokeWidth
    height: m_BoxHeight > spMessage.strokeWidth ? m_BoxHeight : spMessage.strokeWidth

    /**
    * Message shape
    */
    Shape
    {
        // common properties
        id: shMessage
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 8
        smooth: true

        /**
        * Message path
        */
        ShapePath
        {
            // common properties
            id: spMessage
            strokeColor: "black"
            fillColor: "transparent"
            strokeWidth: 1
            startX: itMessage.m_InvertX ? itMessage.width  : 0
            startY: itMessage.m_InvertY ? itMessage.height : 0

            /**
            * Message curve
            */
            PathCubic
            {
                // common properties
                x:         itMessage.m_InvertX ? 0                : itMessage.width
                y:         itMessage.m_InvertY ? 0                : itMessage.height
                control1X: itMessage.m_InvertX ? itMessage.width  : 0
                control1Y: itMessage.m_InvertY ? 0                : itMessage.height
                control2X: itMessage.m_InvertX ? 0                : itMessage.width
                control2Y: itMessage.m_InvertY ? itMessage.height : 0
            }
        }
    }
}
