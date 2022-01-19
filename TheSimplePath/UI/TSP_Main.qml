import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

/**
* Main application window
*@author Jean-Milost Reymond
*/
ApplicationWindow
{
    /**
    * Document status
    */
    enum IEDocStatus
    {
        IE_DS_Closed = 0,
        IE_DS_Opened,
        IE_DS_Error
    }

    // advanced properties
    property ApplicationWindow m_MainWindow:    this
    property var               m_MainFormModel: tspMainFormModel

    // common properties
    id: wiMainWnd
    objectName: "wiMainWnd"
    visible: true
    width: 800
    height: 600
    title: qsTr("The Simple Path")

    Rectangle
    {
        id: rcToolbox
        objectName: "rcToolbox"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 40

        Button
        {
            id: btNewDocument
            objectName: "btNewDocument"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: 75
            text: qsTr("New document")

            onClicked:
            {
                if (m_MainFormModel)
                    m_MainFormModel.onNewDocumentClicked();
            }
        }

        Button
        {
            id: btTest
            objectName: "btTest"
            anchors.left: btNewDocument.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: 75
            text: qsTr("Test")

            onClicked:
            {
                if (m_MainFormModel)
                    m_MainFormModel.onTestClicked();
            }
        }
    }

    /**
    * Rectangle which will contain the document view
    */
    Rectangle
    {
        // common properties
        id: rcDocument
        objectName: "rcDocument"
        color: "#808080"
        anchors.left: parent.left
        anchors.top: rcToolbox.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    /**
    * Document model connections
    */
    Connections
    {
        // common properties
        target: m_MainFormModel

        /**
        * Called when a new document should be created
        *@param {string} name - document name
        *@param {bool} succeeded [out] - whetehr or not the new document was added successfully
        *@return true on success, otherwise false
        */
        function onNewDocument(name)
        {
            if (newDocument(name) === null)
            {
                m_MainFormModel.docStatus = TSP_Main.IEDocStatus.IE_DS_Error;
                return;
            }

            m_MainFormModel.docStatus = TSP_Main.IEDocStatus.IE_DS_Opened;
        }

        /**
        * Called when a row is inserted
        *@param parentIndex - item index which will own the added item(s), if null, item(s) is added to root
        *@param first - first item index to remove
        *@param last - last item index to remove
        */
        /*REM
        function onRowsInserted(parentIndex, first, last)
        {
            //REM showProperDeviceConnectPage();
            return true;
        }
        */

        /**
        * Called when a row is inserted
        *@param parentIndex - item index which will own the added item(s), if null, item(s) is added to root
        *@param first - first item index to remove
        *@param last - last item index to remove
        */
        /*REM
        function onRowsRemoved(parentIndex, first, last)
        {
            //REM showProperDeviceConnectPage();
            return true;
        }
        */
    }

    /**
    * Creates a new document
    *@param name - document name
    *@return newly created document
    */
    function newDocument(name)
    {
        console.log("Create new document... - " + name);

        // load the item component
        let component = Qt.createComponent('TSP_DocumentView.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Create new document - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        // succeeded?
        if (!component)
            return null;

        // create and show new item object
        let item = component.createObject(rcDocument, {"id":         "dvDocumentView_" + name,
                                                       "objectName": "dvDocumentView_" + name,
                                                       "m_Name":                         name});

        console.log("Create new document - succeeded - view name - " + item.objectName);

        return item;
    }
}
