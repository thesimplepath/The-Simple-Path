import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Application document view
*@author Jean-Milost Reymond
*/
T.Frame
{
    // global properties
    property var m_Parent: null
    property var m_Model:  rpmDocumentModel

    // common properties
    id: frDocumentView

    /**
    * Document background
    */
    Rectangle
    {
        // common properties
        anchors.fill: parent
        color: "#808080"

        /**
        * Models stack view
        */
        StackView
        {
            // common properties
            anchors.fill: parent
        }
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        target: m_Model

        /**
        * Called when a row is inserted
        *@param parentIndex [QModelIndex] - parent index which will own the row(s) to insert
        *@param first [QModelIndex] - first added row index
        *@param last [QModelIndex] - last added row index
        */
        function onRowsInserted(parentIndex, first, last)
        {
            console.log("Model(s) inserted in document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }

        /**
        * Called when row(s) is(are) removed
        *@param parentIndex [QModelIndex] - parent index owning the row(s) to remove
        *@param first [QModelIndex] - first removed row index
        *@param last [QModelIndex] - last removed row index
        */
        function onRowsRemoved(parentIndex, first, last)
        {
            console.log("Model(s) removed from document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }
    }

    property int index: 0 // REM FIXME

    /**
    * Adds a message component to the document
    *@param from [var] - symbol the message is attached from
    *@param to [var] - symbol the message is attached to, if null the message is dragging
    *@param fromConn [var] - connector the message is attached from
    *@param toConn [var] - connector the message is attached to, if null the message is dragging
    */
    // todo FIXME -cFeature -oJean: Misplaced, should be moved to model view
    function addMessage(from, to)
    {
            // load the item component
            var component = Qt.createComponent('TSP_Message.qml');

            // succeeded?
            if (component.status !== Component.Ready)
            {
                console.error("Add message - an error occurred while the item was created - " + component.errorString());
                return;
            }

            // create and show new item object
            //var item = component.createObject(frDocumentView, {"id":         "ctMessage" + index,
            var item = component.createObject(m_Parent,       {"id":         "ctMessage" + index, //REM FIXME
                                                               "objectName": "ctMessage" + index,
                                                               "m_From":     from,
                                                               "m_To":       to});
            ++index;
            return item;
    }
}
