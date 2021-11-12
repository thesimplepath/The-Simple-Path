import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Application document view
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_Document: ctDocumentView
    property var m_Model:    rpmDocumentModel

    // common properties
    id: ctDocumentView
    objectName: "ctDocumentView"

    /**
    * Document background
    */
    Rectangle
    {
        // common properties
        id: rcDocumentView
        objectName: "rcDocumentView"
        anchors.fill: parent
        color: "#808080"

        /**
        * Models stack view
        */
        StackView
        {
            // common properties
            id: svDocumentView
            objectName: "svDocumentView"
            anchors.fill: parent
            initialItem: cpAtlasItem
        }

        Component
        {
            id: cpAtlasItem

            TSP_AtlasView
            {}
        }
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        id: cnDocumentView
        objectName: "cnDocumentView"
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
}
