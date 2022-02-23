import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

// javascript
import "js/TSP_JSHelper.js" as JSHelper

/**
* Connector, used to connect two boxes with a link
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Connector position
    *@note This enum is linked with the one located in TSP_QmlBox.
    *      Don't modify it without updating its twin
    */
    enum IEPosition
    {
        IE_P_None = 0,
        IE_P_Left,
        IE_P_Top,
        IE_P_Right,
        IE_P_Bottom
    }

    // aliases
    property alias connectorRect:      rcConnector
    property alias connectorMouseArea: maConnector

    // advanced properties
    property var  m_Box:         null
    property var  m_Links:       []
    property real m_ScaleFactor: 1
    property int  m_Position:    TSP_Connector.IEPosition.IE_P_None

    // common properties
    id: ctConnector
    objectName: "ctConnector"
    width: 14
    height: 14

    /**
    * Connector rectangle
    */
    Rectangle
    {
        // common properties
        id: rcConnector
        objectName: "rcConnector"
        anchors.fill: parent
        color: "white"
        border.color: "#c0c0c0"
        border.width: 3
        radius: 7
    }

    /**
    * Connector mouse area
    */
    MouseArea
    {
        // advanced properties
        property var  m_AddingLinkItem:  null
        property real m_AutoScrollSpeed: 0.0025

        // common properties
        id: maConnector
        objectName: "maConnector"
        anchors.fill: parent
        cursorShape: Qt.CrossCursor
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        /// Called when the mouse button is pressed above the control
        onPressed: function(mouseEvent)
        {
            // add a new link and start to drag it
            if (m_Page && m_Box)
            {
                console.log("Connector - adding a new link - start box - " + m_Box.objectName +
                            " - start connector - "                        + ctConnector.objectName);

                // send signal to notify that a new link should be added from this connector
                m_AddingLinkItem = m_Page.startAddLink(ctConnector);

                // notify the page that a link is currently dragging
                if (m_AddingLinkItem && m_PageContent)
                    m_PageContent.m_DraggingMsg = true;
            }
        }

        /// Called when the mouse button is released after been pressed (above or outside the control)
        onReleased: function(mouseEvent)
        {
            // not adding a link?
            if (!m_AddingLinkItem)
                return;

            // notify the page that the link is no longer dragging
            if (m_PageContent)
                m_PageContent.m_DraggingMsg = false;

            // no document?
            if (!m_Document)
                return;

            let doRemoveMsg = false;
            let targetConn  = undefined;

            try
            {
                let result = [];

                // get all controls located above the mouse onto the document
                JSHelper.getItemsAbovePoint(pageContent, this.mapToGlobal(mouseEvent.x, mouseEvent.y), result);

                // search for target connector
                for (let i = 0; i < result.length; ++i)
                    if (result[i].objectName === m_Box.leftConnector.objectName  ||
                        result[i].objectName === m_Box.topConnector.objectName   ||
                        result[i].objectName === m_Box.rightConnector.objectName ||
                        result[i].objectName === m_Box.bottomConnector.objectName)
                    {
                        // found it? May break the loop if yes, because no connector can overlap another
                        targetConn = result[i];
                        break;
                    }

                // found a valid target connector?
                if (targetConn && targetConn.visible && targetConn.m_Box.boxProxy.uid !== m_Box.boxProxy.uid)
                {
                    console.log("Connector - link added successfully - name - " + m_AddingLinkItem.objectName);

                    // yes, attach the new link to it
                    m_AddingLinkItem.bindTo(targetConn);
                }
                else
                {
                    console.log("Connector - link adding - CANCELED");

                    // no, remove the currently adding link
                    doRemoveMsg = true;
                }
            }
            catch (exception)
            {
                let startBoxName   =  m_Box                           ? m_Box.objectName            : "<unknown>";
                let endBoxName     = (targetConn && targetConn.m_Box) ? targetConn.m_Box.objectName : "<unknown>";
                let targetConnName =  targetConn                      ? targetConn.objectName       : "<unknown>";

                // log error
                console.error("Connector - add link - FAILED - start box name - " + startBoxName           +
                              " - end box name - "                                + endBoxName             +
                              " - start connector - "                             + ctConnector.objectName +
                              " - end connector - "                               + targetConnName         +
                              " - error - "                                       + exception);

                // remove the incompletely added link
                doRemoveMsg = true;
            }

            // do remove the link?
            if (doRemoveMsg)
            {
                m_AddingLinkItem.unbindMsgFromBox(m_Box)
                m_AddingLinkItem.destroy();

                // emit signal that link adding was canceled
                m_Page.linkCanceled();
            }
            else
                // emit signal that link was added
                m_Page.linkAdded(m_AddingLinkItem);

            // since now link is no longer adding
            m_AddingLinkItem = undefined;
        }

        /// called when mouse moved on the x axis above the handle
        onMouseXChanged: function(mouseEvent)
        {
            // not adding a link?
            if (!m_AddingLinkItem)
                return;

            if (!pressed)
                return;

            if (m_PageContent)
            {
                // convert mouse pointer to page content coordinate system
                const localMouse = mapToItem(m_PageContent, mouseEvent.x, mouseEvent.y);
                const pointX     = localMouse.x * m_ScaleFactor;
                const pointY     = localMouse.y * m_ScaleFactor;

                // notify page that auto-scroll may be applied
                m_PageContent.doAutoScroll(pointX, pointX, pointY, pointY);
            }
        }

        /// called when mouse moved on the y axis above the handle
        onMouseYChanged: function(mouseEvent)
        {
            // not adding a link?
            if (!m_AddingLinkItem)
                return;

            if (!pressed)
                return;

            if (m_PageContent)
            {
                // convert mouse pointer to page content coordinate system
                const localMouse = mapToItem(m_PageContent, mouseEvent.x, mouseEvent.y);
                const pointX     = localMouse.x * m_ScaleFactor;
                const pointY     = localMouse.y * m_ScaleFactor;

                // notify page that auto-scroll may be applied
                m_PageContent.doAutoScroll(pointX, pointX, pointY, pointY);
            }
        }
    }

    /**
    * Signal connectors
    */
    Connections
    {
        target: pageContent

        /**
        * Called when the page scale factor changed
        *@param {number} factor - scale factor
        */
        function onPageScaleChanged(factor)
        {
            m_ScaleFactor = factor;
        }
    }
}
