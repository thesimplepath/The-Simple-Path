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
    property var m_Target:    null
    property int m_Direction: IEDirection.IE_D_None;

    // common properties
    id: ctHandle
    width: 7
    height: 7

    /**
    * Handle rectangle
    */
    Rectangle
    {
        // common properties
        id: rcHandle
        anchors.fill: parent
        color: "#c0c0c0"
        border.color: "black"
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
        anchors.fill: parent
        cursorShape: getCursorShape(ctHandle.m_Direction)
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        /// called when mouse moved on the x axis above the handle
        onMouseXChanged:
        {
            if (!ctHandle.m_Target)
                return;

            if (!pressed)
                return;

            switch (ctHandle.m_Direction)
            {
                case TSP_Handle.IEDirection.IE_D_Left:
                case TSP_Handle.IEDirection.IE_D_LeftTop:
                case TSP_Handle.IEDirection.IE_D_LeftBottom:
                    ctHandle.m_Target.x     += mouseX;
                    ctHandle.m_Target.width -= mouseX;

                    if (ctHandle.m_Target.x < 0 || ctHandle.m_Target.width < 30)
                    {
                        ctHandle.m_Target.x     -= mouseX;
                        ctHandle.m_Target.width += mouseX;
                    }

                    break;

                case TSP_Handle.IEDirection.IE_D_Right:
                case TSP_Handle.IEDirection.IE_D_RightTop:
                case TSP_Handle.IEDirection.IE_D_RightBottom:
                    ctHandle.m_Target.width += mouseX;

                    if (ctHandle.m_Target.width < 30)
                        ctHandle.m_Target.width -= mouseX;

                    break;
            }
        }

        /// called when mouse moved on the y axis above the handle
        onMouseYChanged:
        {
            if (!ctHandle.m_Target)
                return;

            if (!pressed)
                return;

            switch (ctHandle.m_Direction)
            {
                case TSP_Handle.IEDirection.IE_D_Top:
                case TSP_Handle.IEDirection.IE_D_LeftTop:
                case TSP_Handle.IEDirection.IE_D_RightTop:
                    ctHandle.m_Target.y      += mouseY;
                    ctHandle.m_Target.height -= mouseY;

                    if (ctHandle.m_Target.y < 0 || ctHandle.m_Target.height < 30)
                    {
                        ctHandle.m_Target.y      -= mouseY;
                        ctHandle.m_Target.height += mouseY;
                    }

                    break;

                case TSP_Handle.IEDirection.IE_D_Bottom:
                case TSP_Handle.IEDirection.IE_D_LeftBottom:
                case TSP_Handle.IEDirection.IE_D_RightBottom:
                    ctHandle.m_Target.height += mouseY;

                    if (ctHandle.m_Target.height < 30)
                        ctHandle.m_Target.height -= mouseY;

                    break;
            }
        }
    }

    /**
    * Gets the cursor shape to show for this handle
    *@param direction - direction the handle is moving
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
