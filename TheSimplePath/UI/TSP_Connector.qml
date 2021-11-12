import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

// javascript
import "TSP_JSHelper.js" as JSHelper

/**
* Connector, used to connect two symbols with a message
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Connector position
    */
    enum IEPosition
    {
        IE_P_None,
        IE_P_Left,
        IE_P_Top,
        IE_P_Right,
        IE_P_Bottom
    }

    // aliases
    property alias connectorRect:      rcConnector
    property alias connectorMouseArea: maConnector

    // advanced properties
    property var m_Box:      null
    property var m_Messages: []
    property int m_Position: TSP_Connector.IEPosition.IE_P_None

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
        color: "transparent"
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
        property var m_AddingMsg: null

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
            // add a new message and start to drag it
            if (m_Page && m_Box)
            {
                console.log("Connector - adding a new message - start box - " + m_Box.objectName +
                            " - start connector - "                           + ctConnector.objectName);

                m_AddingMsg = m_Page.addMessage(ctConnector, null);
            }
        }

        /// Called when the mouse button is released after been pressed (above or outside the control)
        onReleased: function(mouseEvent)
        {
            // not adding a new message?
            if (!m_AddingMsg)
                return;

            // no document?
            if (!m_Document)
                return;

            let doRemoveMsg = false;
            let targetConn  = null;

            try
            {
                let result = [];

                // get all controls located above the mouse onto the document
                JSHelper.getItemsAbovePoint(m_Document, this.mapToGlobal(mouseEvent.x, mouseEvent.y), result);

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
                if (targetConn && targetConn.m_Box != m_Box)
                {
                    console.log("Connector - message added successfully - name - " + m_AddingMsg.objectName);

                    // yes, attach the new message to it
                    m_AddingMsg.m_To = targetConn;
                }
                else
                {
                    console.log("Connector - message adding - CANCELED");

                    // no, remove the currently adding message
                    doRemoveMsg = true;
                }
            }
            catch (exception)
            {
                let startBoxName   =  m_Box                           ? m_Box.objectName            : "<unknown>";
                let endBoxName     = (targetConn && targetConn.m_Box) ? targetConn.m_Box.objectName : "<unknown>";
                let targetConnName =  targetConn                      ? targetConn.objectName       : "<unknown>";

                // log error
                console.error("Connector - add message - FAILED - start box name - " + startBoxName           +
                              " - end box name - "                                   + endBoxName             +
                              " - start connector - "                                + ctConnector.objectName +
                              " - end connector - "                                  + targetConnName         +
                              " - error - "                                          + exception);

                // remove the incompletely added message
                doRemoveMsg = true;
            }

            // do remove the message?
            if (doRemoveMsg)
            {
                m_AddingMsg.unbindMsgFromBox(m_Box)
                m_AddingMsg.destroy();
            }

            // since now message is no longer adding
            m_AddingMsg = null;
        }
    }
}
