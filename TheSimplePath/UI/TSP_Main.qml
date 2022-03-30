import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.1

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
    title: qsTrId("app-name")

    /**
    * Error message dialog
    */
    MessageDialog
    {
        // common properties
        id: mdError
        objectName: "mdError"
        icon: StandardIcon.Critical
        standardButtons: StandardButton.Ok
        visible: false

        /// called when user clicked on the Ok button
        onAccepted:
        {
            close();
        }
    }

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
            text: qsTrId("new-document")

            /// called when button is clicked
            onClicked:
            {
                console.log("GUI - New document clicked");

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
            text: qsTrId("close-document")

            /// called when button is clicked
            onClicked:
            {
                console.log("GUI - Close document clicked");

                if (m_MainFormModel)
                    m_MainFormModel.onCloseDocumentClicked();
            }
        }

        /**
        * Add process button
        */
        Button
        {
            // common properties
            id: btAddProcess
            objectName: "btAddProcess"
            anchors.left: btCloseDocument.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: qsTrId("add-process")

            /// called when button is clicked
            onClicked:
            {
                console.log("GUI - Add process clicked");

                if (m_MainFormModel)
                    m_MainFormModel.onAddProcessClicked();
            }
        }

        /**
        * Add box button
        */
        // FIXME for Jean: remove when useless
        Button
        {
            // common properties
            id: btAddbox
            objectName: "btAddBox"
            anchors.left: btAddProcess.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: qsTrId("add-box")

            /// called when button is clicked
            onClicked:
            {
                console.log("GUI - Add box clicked");

                if (m_MainFormModel)
                    m_MainFormModel.onAddBoxClicked();
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

                /**
                * Document loader
                */
                Loader
                {
                    // common properties
                    id: ldDocument
                    objectName: "ldDocument"
                    anchors.fill: parent
                }
            }
        }
    }

    /**
    * Main form model connections
    */
    Connections
    {
        // common properties
        id: cnMainForm
        objectName: "cnMainForm"
        target: m_MainFormModel

        /**
        * Called when an error message should be shown
        *@param {string} title - dialog title
        *@param {string} msg - error message
        *@param {string} detailedMsg - detailed error message, ignored if empty
        */
        function onShowErrorDialog(title, msg, detailedMsg)
        {
            // show the error dialog box
            mdError.title        = title;
            mdError.text         = msg;
            mdError.detailedText = detailedMsg;
            mdError.open();
        }
    }

    /**
    * Document model connections
    */
    Connections
    {
        // common properties
        id: cnDocModel
        objectName: "cnDocModel"
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
            if (!result)
            {
                // notify the model about the error
                tspDocumentModel.docStatus = TSP_DocumentView.IEDocStatus.IE_DS_Error;
                return;
            }

            // update the form title
            title = qsTrId("app-name") + " - " + name;
        }

        /**
        * Called when the document view should be deleted
        */
        function onDeleteDocumentView()
        {
            deleteDocumentView();

            // update the form title
            title = qsTrId("app-name");
        }
    }

    /**
    * Creates a new document view
    *@param {string} name - document name
    *@param {number} openedCount - document opened count
    *@return newly created document, undefined on error
    */
    function createDocumentView(name, openedCount)
    {
        try
        {
            console.log("Create document - name - " + name);

            // build document identifier
            const docId = "dvDocumentView_" + openedCount;

            // create a new document view
            ldDocument.setSource("TSP_DocumentView.qml", {"id":         docId,
                                                          "objectName": docId,
                                                          "m_Name":     name});

            // succeeded?
            if (!ldDocument.item)
            {
                console.error("Create document - FAILED - an error occurred while the view was created");
                return undefined;
            }

            console.log("Create document - succeeded - view name - " + ldDocument.item.objectName);

            return ldDocument.item;
        }
        catch (e)
        {
            console.exception("Create document - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // delete the document, if previously created
        ldDocument.source = "";

        return undefined;
    }

    /**
    * Deletes the currently opened document view
    */
    function deleteDocumentView()
    {
        try
        {
            // no document opened?
            if (!ldDocument.item)
                return;

            console.log("Delete document - view name - " + ldDocument.item.objectName);

            // delete the document
            ldDocument.source = "";

            console.log("Delete document - succeeded");
        }
        catch (e)
        {
            console.exception("Delete document - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }
    }
}
