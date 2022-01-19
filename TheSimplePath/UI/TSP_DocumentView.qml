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
    property var    m_Document: this
    property var    m_Model:    tspDocumentModel
    property string m_Name:     ""
    property int    m_GenIndex: 0

    // common properties
    id: ctDocumentView
    objectName: "ctDocumentView"
    anchors.fill: parent

    /**
    * Document background
    */
    Rectangle
    {
        // common properties
        id: rcDocumentView
        objectName: "rcDocumentView"
        anchors.fill: parent
        color: "white"

        /**
        * Models stack view
        */
        StackView
        {
            // common properties
            id: svDocumentView
            objectName: "svDocumentView"
            anchors.fill: parent
            initialItem: null//cpAtlasItem//null
        }

        /*
        //REM FIXME
        Component.onCompleted:
        {
            addAtlas();
        }
        */
        /*REM
        Component
        {
            id: cpAtlasItem

            TSP_AtlasView
            {}
        }
        */
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
        *@param {QModelIndex} parentIndex - parent index which will own the row(s) to insert
        *@param {QModelIndex} first - first added row index
        *@param {QModelIndex} last - last added row index
        */
        function onRowsInserted(parentIndex, first, last)
        {
            console.log("Atlas(es) inserted in document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);

            addAtlas();
        }

        /**
        * Called when row(s) is(are) removed
        *@param {QModelIndex} parentIndex - parent index owning the row(s) to remove
        *@param {QModelIndex} first - first removed row index
        *@param {QModelIndex} last - last removed row index
        */
        function onRowsRemoved(parentIndex, first, last)
        {
            console.log("Atlas(es) removed from document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }
    }

    /**
    * Adds an atlas
    *@return newly created atlas, null on error
    */
    function addAtlas()
    {
        // FIXME
        let name = "MyAtlas";
        console.log("Create new atlas... - " + name);

        // load the item component
        let component = Qt.createComponent('TSP_AtlasView.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add atlas - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        let m_GenIndex = 1;

        // create and show new item object
        let item = component.createObject(svDocumentView, {"id":         "atAtlas" + m_GenIndex,
                                                           "objectName": "atAtlas" + m_GenIndex});

        // show the newly added atlas onto the document view
        svDocumentView.push(item);

        console.log("Add atlas - succeeded - new item - " + item.objectName);

        ++m_GenIndex;

        return item;
    }
}
