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
        color: Styles.m_DocumentBgColor

        /**
        * Atlas stack model
        */
        ListModel
        {
            // common properties
            id: lmAtlasStack
            objectName: "lmAtlasStack"
        }

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

            /**
            * Atlas repeater
            */
            Repeater
            {
                // common properties
                id: rpAtlasStack
                objectName: "rpAtlasStack"
                model: lmAtlasStack

                /**
                * Atlas view template
                */
                TSP_AtlasView
                {
                    // advanced properties
                    id:             atlasID
                    objectName:     atlasObjName
                    atlasProxy.uid: uid
                }
            }
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
            removeAtlas(uid, true);
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
            const atlasView = rpAtlasStack.itemAt(slAtlasStack.currentIndex);

            // found it?
            if (!atlasView)
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
    *@return newly created atlas, undefined on error
    */
    function addAtlas(uid)
    {
        try
        {
            // cannot create an atlas if its uid is invalid
            if (!uid.length)
            {
                console.error("Add atlas - FAILED - cannot create atlas if unique identifier is empty");
                return undefined;
            }

            console.log("Add atlas - uid - " + uid);

            // build atlas identifier
            const atlasId = "atAtlas_" + uid;

            // add a new atlas on the stack end
            lmAtlasStack.append({"uid": uid, "atlasID": atlasId, "atlasObjName": atlasId});

            // get the newly added atlas
            let item = rpAtlasStack.itemAt(slAtlasStack.count - 1);

            // found it?
            if (!item || item.atlasProxy.uid !== uid)
            {
                console.error("Add atlas - an error occurred while the view was created");
                return undefined;
            }

            console.log("Add atlas - succeeded - view name - " + item.objectName);

            return item;
        }
        catch (e)
        {
            console.exception("Add atlas - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // remove the partially added atlas, if any
        removeAtlas(uid, false);

        return undefined;
    }

    /**
    * Removes an atlas from the document view
    *@param {string} uid - atlas unique identifier
    *@param {bool} verbose - if true, the error and success messages will be logged
    */
    function removeAtlas(uid, verbose)
    {
        try
        {
            // cannot remove an atlas if its uid is invalid
            if (!uid.length)
                return;

            if (verbose)
                console.log("Remove atlas - uid - " + uid);

            let atlasName;
            let index = -1;

            // iterate through atlas views
            for (var i = 0; i < rpAtlasStack.count; ++i)
            {
                // get child
                let child = rpAtlasStack.itemAt(i);

                if (!child)
                {
                    console.warn("Remove atlas - invalid child - index - " + i + " - count - " + rpAtlasStack.count);
                    continue;
                }

                // found the atlas to delete?
                if (child instanceof TSP_AtlasView && child.atlasProxy.uid === uid)
                {
                    // keep the atlas name for logging
                    atlasName = slAtlasStack.children[i].objectName;

                    // get the atlas index to delete
                    index = i;

                    break;
                }
            }

            // found the atlas to delete?
            if (index < 0)
            {
                if (verbose)
                    console.log("Remove atlas - FAILED - view not found");

                return;
            }

            // delete atlas
            lmAtlasStack.remove(index);

            // log deleted atlas
            if (verbose && atlasName && atlasName.length)
                console.log("Remove atlas - view was removed - view name - " + atlasName);

            if (verbose)
                console.log("Remove atlas - succeeded");
        }
        catch (e)
        {
            console.exception("Remove atlas - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }
    }
}
