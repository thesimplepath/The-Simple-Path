import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Templates 2.15 as T

// c++
import thesimplepath.proxys 1.0

/**
* Atlas view
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias atlasProxy: apAtlasProxy

    // advanced properties
    property var    m_Atlas:   this
    property string m_Type:    "TSP_AtlasView"
    property bool   m_Deleted: false

    // common properties
    id: ctAtlasView
    objectName: "ctAtlasView"

    /**
    * Atlas proxy
    *@note This component will auto-create a new c++ TSP_QmlAtlasProxy instance
    */
    AtlasProxy
    {
        // common properties
        id: apAtlasProxy
        objectName: "apAtlasProxy"
    }

    /**
    * Page stack view
    */
    StackLayout
    {
        // common properties
        id: slPageStack
        objectName: "slPageStack"
        anchors.fill: parent
        currentIndex: 0
        clip: true

        /// called when page is loaded
        Component.onCompleted:
        {
            addPage("1234");
        }
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        target: tspPageListModel

        function onTestSignal()
        {
            console.log("***** ***** This signal ALSO!!!");
        }
    }

    /**
    * Creates a new page and adds it to the atlas view
    *@param uid - page unique identifier
    *@return newly created page, null on error
    */
    function addPage(uid)
    {
        // cannot create a page if its uid is invalid
        if (!uid.length)
        {
            console.error("Add page - FAILED - cannot create page if unique identifier is empty");
            return null;
        }

        console.log("Add page - uid - " + uid);

        // load the item component
        let component = Qt.createComponent('TSP_SymbolPageView.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add page - an error occurred while the item was created - " + component.errorString());
            return null;
        }

        // build page identifier
        const pageId = "paPage_" + uid;

        // create and show new item object
        let item = component.createObject(slPageStack, {"id":         pageId,
                                                        "objectName": pageId});

        // succeeded?
        if (!item)
        {
            console.error("Add page - an error occurred while the item was added to atlas");
            return null;
        }

        // declare the unique identifier in the page proxy
        item.pageProxy.uid = uid;

        // show the newly added page onto the atlas view
        slPageStack.currentIndex = slPageStack.count - 1;

        console.log("Add page - succeeded - new item - object name - " + item.objectName);

        return item;
    }

    /**
    * Removes a page from the atlas view
    *@param uid - page unique identifier
    */
    function removePage(uid)
    {
        // cannot remove a page if its uid is invalid
        if (!uid.length)
            return;

        console.log("Remove page - uid - " + uid);

        var pageName;
        var deleted = false;

        // iterate through page view stack until find the view to delete, and deletes it
        for (var i = slPageStack.children.length - 1; i >= 0; --i)
            // found the atlas to delete?
            if (slPageStack.children[i].m_Type        === "TSP_SymbolPageView" &&
               !slPageStack.children[i].m_Deleted                              &&
                slPageStack.children[i].pageProxy.uid === uid)
            {
                // keep the page name for logging
                pageName = slPageStack.children[i].objectName;

                // NOTE setting the deleted property just before destroying the component may seem incoherent,
                // however the destroyed item is kept in memory until the garbage collector deletes it, and may
                // be thus still found when the children are iterated. This may cause a deleting item to be
                // processed as a normal item in other situations where it shouldn't
                slPageStack.children[i].m_Deleted = true;
                slPageStack.children[i].destroy();

                deleted = true;
                break;
            }

        // log success or failure
        if (deleted)
            console.log("Remove page - succeeded - view name - " + atlasName);
        else
            console.error("Remove page - FAILED");
    }
}
