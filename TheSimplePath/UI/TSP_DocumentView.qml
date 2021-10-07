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
    property var m_Model: rpmDocumentModel

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
        *@param parentIndex - parent index which will own the row(s) to insert
        *@param first - first added row index
        *@param last - last added row index
        */
        function onRowsInserted(parentIndex, first, last)
        {
            console.log("Model(s) inserted in document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }

        /**
        * Called when row(s) is(are) removed
        *@param parentIndex - parent index owning the row(s) to remove
        *@param first - first removed row index
        *@param last - last removed row index
        */
        function onRowsRemoved(parentIndex, first, last)
        {
            console.log("Model(s) removed from document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }
    }
}
