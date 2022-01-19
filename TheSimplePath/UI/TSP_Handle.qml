import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Handle, used to resize the control
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Handle moving directions
    */
    enum IEDirection
    {
        IE_D_None,
        IE_D_Left,
        IE_D_LeftTop,
        IE_D_Top,
        IE_D_RightTop,
        IE_D_Right,
        IE_D_RightBottom,
        IE_D_Bottom,
        IE_D_LeftBottom
    }

    // aliases
    property alias handleRect: rcHandle

    // advanced properties
    property var    m_Target:      null
    property string m_Color:       "#c0c0c0"
    property string m_BorderColor: "black"
    property int    m_Direction:   IEDirection.IE_D_None

    // common properties
    id: ctHandle
    objectName: "ctHandle"
    width: 7
    height: 7

    /**
    * Handle rectangle
    */
    Rectangle
    {
        // common properties
        id: rcHandle
        objectName: "rcHandle"
        anchors.fill: parent
        color: m_Color
        border.color: m_BorderColor
        border.width: 1
        radius: 3
    }

    /**
    * Handle mouse area
    */
    MouseArea
    {
        // common properties
        id: maHandle
        objectName: "maHandle"
        anchors.fill: parent
        cursorShape: getCursorShape(ctHandle.m_Direction)
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        /// called when mouse moved on the x axis above the handle
        onMouseXChanged:
        {
            if (!pressed)
                return;

            if (m_Target)
                m_Target.resize(m_Direction, mouseX, 0);
        }

        /// called when mouse moved on the y axis above the handle
        onMouseYChanged:
        {
            if (!pressed)
                return;

            if (m_Target)
                m_Target.resize(m_Direction, 0, mouseY);
        }
    }

    /**
    * Gets the cursor shape to show for this handle
    *@param {IEDirection} direction - direction the handle is moving
    *@return cursor shape to show
    */
    function getCursorShape(direction)
    {
        switch (direction)
        {
            case TSP_Handle.IEDirection.IE_D_Left:        return Qt.SizeHorCursor;
            case TSP_Handle.IEDirection.IE_D_LeftTop:     return Qt.SizeFDiagCursor;
            case TSP_Handle.IEDirection.IE_D_Top:         return Qt.SizeVerCursor;
            case TSP_Handle.IEDirection.IE_D_RightTop:    return Qt.SizeBDiagCursor;
            case TSP_Handle.IEDirection.IE_D_Right:       return Qt.SizeHorCursor;
            case TSP_Handle.IEDirection.IE_D_RightBottom: return Qt.SizeFDiagCursor;
            case TSP_Handle.IEDirection.IE_D_Bottom:      return Qt.SizeVerCursor;
            case TSP_Handle.IEDirection.IE_D_LeftBottom:  return Qt.SizeBDiagCursor;
        }

        return Qt.ArrowCursor;
    }
}
