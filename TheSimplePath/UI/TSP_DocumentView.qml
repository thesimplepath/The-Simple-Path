import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Templates 2.15 as T

/**
* Document view
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Document status
    *@note This enum is linked with the one located in TSP_Document.
    *      Don't modify it without updating its twin
    */
    enum IEDocStatus
    {
        IE_DS_Closed = 0,
        IE_DS_Opening,
        IE_DS_Opened,
        IE_DS_Error
    }

    // advanced properties
    property var    m_Document: this
    property var    m_Model:    tspDocumentModel
    property string m_Name:     ""
    property string m_Type:     "TSP_DocumentView"
    property bool   m_Deleted:  false

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
        * Atlas view stack
        */
        StackLayout
        {
            // common properties
            id: slAtlasStack
            objectName: "slAtlasStack"
            anchors.fill: parent
            clip: true
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
        * Called when an atlas should be added to the document view
        *@param {string} uid - atlas unique identifier to add
        */
        function onAddAtlasToView(uid)
        {
            addAtlas(uid);
        }

        /**
        * Called when an atlas should be removed from the document view
        *@param {string} uid - atlas unique identifier to remove
        */
        function onRemoveAtlasFromView(uid)
        {
            removeAtlas(uid);
        }

        /**
        * Called when the currently selected atlas is queried
        */
        function onQueryAtlasUID()
        {
            if (!m_Model)
                return;

            // no current index selected?
            if (slAtlasStack.currentIndex < 0)
            {
                m_Model.onSelectedAtlasChanged("");
                return;
            }

            // get the selected atlas view
            const atlasView = slAtlasStack.children[slAtlasStack.currentIndex];

            // found it?
            if (atlasView === null || atlasView === undefined)
            {
                m_Model.onSelectedAtlasChanged("");
                return;
            }

            // notify the model about the currently selected atlas
            m_Model.selectedAtlasUID = atlasView.atlasProxy.uid;
        }

        /**
        * Called when a row is inserted
        *@param {QModelIndex} parentIndex - parent index which will own the row(s) to insert
        *@param {QModelIndex} first - first added row index
        *@param {QModelIndex} last - last added row index
        */
        function onRowsInserted(parentIndex, first, last)
        {
            console.log("Atlas(es) inserted in document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
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
    * Creates a new atlas and adds it to the document view
    *@param {string} uid - atlas unique identifier
    *@return newly created atlas, null on error
    */
    function addAtlas(uid)
    {
        // cannot create an atlas if its uid is invalid
        if (!uid.length)
        {
            console.error("Add atlas - FAILED - cannot create atlas if unique identifier is empty");
            return null;
        }

        console.log("Add atlas - uid - " + uid);

        // load the item component
        let component = Qt.createComponent('TSP_DocAtlasView.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add atlas - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        // build atlas identifier
        const atlasId = "atAtlas_" + uid;

        // create and show new item object
        let item = component.createObject(slAtlasStack, {"id":         atlasId,
                                                         "objectName": atlasId});

        // succeeded?
        if (!item)
        {
            console.error("Add atlas - an error occurred while the item was added to document");
            return null;
        }

        // declare the unique identifier in the atlas proxy
        item.atlasProxy.uid = uid;

        // show the newly added atlas onto the document view
        slAtlasStack.currentIndex = slAtlasStack.count - 1;

        console.log("Add atlas - succeeded - new item - object name - " + item.objectName);

        return item;
    }

    /**
    * Removes an atlas from the document view
    *@param {string} uid - atlas unique identifier
    */
    function removeAtlas(uid)
    {
        // cannot remove an atlas if its uid is invalid
        if (!uid.length)
            return;

        console.log("Remove atlas - uid - " + uid);

        let atlasName;

        // iterate through atlas view stack until find the view to delete, and deletes it
        for (let i = slAtlasStack.children.length - 1; i >= 0; --i)
            // found the atlas to delete?
            if (slAtlasStack.children[i].m_Type         === "TSP_DocAtlasView" &&
               !slAtlasStack.children[i].m_Deleted                             &&
                slAtlasStack.children[i].atlasProxy.uid === uid)
            {
                // keep the atlas name for logging
                atlasName = slAtlasStack.children[i].objectName;

                // NOTE setting the deleted property just before destroying the component may seem incoherent,
                // however the destroyed item is kept in memory until the garbage collector deletes it, and may
                // be thus still found when the children are iterated. This may cause a deleting item to be
                // processed as a normal item in other situations where it shouldn't
                slAtlasStack.children[i].m_Deleted = true;
                slAtlasStack.children[i].destroy();
                break;
            }

        // log deleted atlas
        if (atlasName.length)
            console.log("Remove atlas - view was removed - name - " + atlasName);

        console.log("Remove atlas - succeeded");
    }
}
