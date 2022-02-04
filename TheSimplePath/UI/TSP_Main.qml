import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15

// javascript
import "js/TSP_JSHelper.js" as JSHelper

/**
* Main application window
*@author Jean-Milost Reymond
*/
ApplicationWindow
{
    // advanced properties
    property ApplicationWindow m_MainWindow:       this
    property var               m_MainFormModel:    tspMainFormModel
    property real              m_PageListMinWidth: 0.1 // minimum width the page list view may take, in percent (between 0.0 and 1.0)
    property real              m_PageListMaxWidth: 0.9 // maximum width the page list view may take, in percent (between 0.0 and 1.0)

    // common properties
    id: wiMainWnd
    objectName: "wiMainWnd"
    visible: true
    width: 800
    height: 600
    title: qsTr("The Simple Path")

    /**
    * Toolbox
    */
    Rectangle
    {
        id: rcToolbox
        objectName: "rcToolbox"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 40

        /**
        * Create document button
        */
        Button
        {
            // common properties
            id: btNewDocument
            objectName: "btNewDocument"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: 75
            text: qsTr("New document")

            /// called when button is clicked
            onClicked:
            {
                if (m_MainFormModel)
                    m_MainFormModel.onNewDocumentClicked();
            }
        }

        /**
        * Close document button
        */
        Button
        {
            // common properties
            id: btCloseDocument
            objectName: "btCloseDocument"
            anchors.left: btNewDocument.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: 75
            text: qsTr("Close document")

            /// called when button is clicked
            onClicked:
            {
                if (m_MainFormModel)
                    m_MainFormModel.onCloseDocumentClicked();
            }
        }
    }

    /**
    * Main view
    */
    SplitView
    {
        // common properties
        id: svMainSplitView
        objectName: "svMainSplitView"
        anchors.left: parent.left
        anchors.top: rcToolbox.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: Qt.Horizontal

        /**
        * Page list view
        */
        TSP_PageListView
        {
            // common properties
            id: plPageListView
            objectName: "plPageListView"
            implicitWidth: 150
            Layout.fillWidth: false
            Layout.fillHeight: true

            /// called when width changed
            onWidthChanged:
            {
                // calculate the minimum and maximum width
                const minWidth = parent.width * JSHelper.clamp01(m_PageListMinWidth);
                const maxWidth = parent.width * JSHelper.clamp01(m_PageListMaxWidth);

                // bounds the page list width
                if (width < minWidth)
                    width = minWidth;
                else
                if (width > maxWidth)
                    width = maxWidth;
            }
        }

        /**
        * Document background
        */
        Rectangle
        {
            id: rcDocBg
            objectName: "rcDocBg"
            Layout.fillWidth: true
            Layout.fillHeight: true

            /**
            * Rectangle which will contain the document view
            */
            Rectangle
            {
                // common properties
                id: rcDocument
                objectName: "rcDocument"
                color: "#808080"
                anchors.fill: parent
            }
        }
    }

    /**
    * Document model connections
    */
    Connections
    {
        // common properties
        id: cnMainView
        objectName: "cnMainView"
        target: tspDocumentModel

        /**
        * Called when a new document view should be created
        *@param {string} name - document name
        *@param {number} openedCount - document opened count
        */
        function onCreateDocumentView(name, openedCount)
        {
            // create a new document view
            const result = createDocumentView(name, openedCount);

            // succeeded?
            if (result === null || result === undefined)
            {
                // notify the model about the error
                tspDocumentModel.docStatus = TSP_DocumentView.IEDocStatus.IE_DS_Error;
                return;
            }

            // update the form title
            title = qsTr("The Simple Path") + " - " + name;
        }

        /**
        * Called when the document view should be deleted
        */
        function onDeleteDocumentView()
        {
            deleteDocumentView();

            // update the form title
            title = qsTr("The Simple Path");
        }
    }

    /**
    * Creates a new document view
    *@param {string} name - document name
    *@param {number} openedCount - document opened count
    *@return newly created document, null on error
    */
    function createDocumentView(name, openedCount)
    {
        console.log("Create new document view - " + name);

        // load the item component
        let component = Qt.createComponent('TSP_DocumentView.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Create new document view - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        // succeeded?
        if (!component)
            return null;

        // create and show new item object
        let item = component.createObject(rcDocument, {"id":         "dvDocumentView_" + openedCount,
                                                       "objectName": "dvDocumentView_" + openedCount,
                                                       "m_Name":                         name});

        console.log("Create new document view - succeeded - view name - " + item.objectName);

        return item;
    }

    /**
    * Deletes the currently opened document view
    */
    function deleteDocumentView()
    {
        var docName;
        var deleted = false;

        // iterate through document view container until find the view to delete, and deletes it
        for (var i = rcDocument.children.length - 1; i >= 0; --i)
            // is component a document view?
            if (rcDocument.children[i].m_Type === "TSP_DocumentView" && !rcDocument.children[i].m_Deleted)
            {
                // keep the document name for logging
                docName = rcDocument.children[i].objectName;

                // NOTE setting the deleted property just before destroying the component may seem incoherent,
                // however the destroyed item is kept in memory until the garbage collector deletes it, and may
                // be thus still found when the children are iterated. This may cause a deleting item to be
                // processed as a normal item in other situations where it shouldn't
                rcDocument.children[i].m_Deleted = true;
                rcDocument.children[i].destroy();

                deleted = true;
                break;
            }

        // log success or failure
        if (deleted)
            console.log("Delete document view - succeeded - view name - " + docName);
        else
            console.error("Delete document view - FAILED");
    }
}
