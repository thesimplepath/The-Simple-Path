import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Templates 2.15 as T

/**
* Pages view
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias pageStack: slPageStack

    // advanced properties
    property var m_PagesView: this

    // common properties
    id: ctPagesView
    objectName: "ctPagesView"

    /**
    * Page stack model
    */
    ListModel
    {
        // common properties
        id: lmPageStack
        objectName: "lmPageStack"
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

        /**
        * Page repeater
        */
        Repeater
        {
            // common properties
            id: rpPageStack
            objectName: "rpPageStack"
            model: lmPageStack

            /**
            * Page view template
            */
            TSP_PageView
            {
                // advanced properties
                id:            pageID
                objectName:    pageObjName
                pageProxy.uid: uid
            }
        }
    }

    /**
    * Page list view model connections
    */
    Connections
    {
        // common properties
        id: cnPageListView
        objectName: "cnPageListView"
        target: tspPageListModel

        /**
        * Called when the selected page should be shown
        *@param {number} index - selected page index, -1 if no selected page
        *@param {string} uid - page unique identifier, empty string if no selected page
        */
        function onShowSelectedPage(index, uid)
        {
            try
            {
                // if no unique identifier defined, don't show page
                if (!uid || !uid.length)
                {
                    slPageStack.currentIndex = -1;
                    return;
                }

                // iterate through page view stack until find the matching page unique identifier
                for (var i = 0; i < rpPageStack.count; ++i)
                {
                    // get child
                    let child = rpPageStack.itemAt(i);

                    if (!child)
                    {
                        console.warn("On show selected page - invalid child - index - " + i + " - count - " + rpAtlasStack.count);
                        continue;
                    }

                    // found page to show?
                    if (child instanceof TSP_PageView && child.pageProxy.uid === uid)
                    {
                        slPageStack.currentIndex = i;
                        break;
                    }
                }
            }
            catch (e)
            {
                console.exception("On show selected page - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
            }
        }
    }

    /**
    * Creates a new page and adds it to the atlas view
    *@param {string} uid - page unique identifier
    *@param show - if true the newly added page will be shown immediately
    *@return newly created page, undefined on error
    */
    function addPage(uid, show)
    {
        try
        {
            // cannot create a page if its uid is invalid
            if (!uid || !uid.length)
            {
                console.error("Add page - FAILED - cannot create page if unique identifier is empty");
                return undefined;
            }

            console.log("Add page - uid - " + uid);

            // save current index and build page identifier
            const curIndex = slPageStack.currentIndex;
            const pageId   = "paPage_" + uid;

            // add a new page on the stack end
            lmPageStack.append({"uid": uid, "pageID": pageId, "pageObjName": pageId});

            // get the newly added page
            let item = rpPageStack.itemAt(rpPageStack.count - 1);

            // found it?
            if (!item || item.pageProxy.uid !== uid)
            {
                console.error("Add page - an error occurred while the view was created");
                return undefined;
            }

            // do show the newly added page?
            if (!show)
                slPageStack.currentIndex = curIndex;

            console.log("Add page - succeeded - view name - " + item.objectName);

            return item;
        }
        catch (e)
        {
            console.exception("Add page - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // remove the partially added page, if any
        removePage(uid, false);

        return undefined;
    }

    /**
    * Removes a page from the atlas view
    *@param {string} uid - page unique identifier
    *@param {bool} verbose - if true, the error and success messages will be logged
    */
    function removePage(uid, verbose)
    {
        try
        {
            // cannot remove a page if its uid is invalid
            if (!uid || !uid.length)
                return;

            if (verbose)
                console.log("Remove page - uid - " + uid);

            let pageName;
            let index = -1;

            // iterate through page views
            for (var i = 0; i < rpPageStack.count; ++i)
            {
                // get child
                let child = rpPageStack.itemAt(i);

                if (!child)
                {
                    console.warn("Remove page - invalid child - index - " + i + " - count - " + rpAtlasStack.count);
                    continue;
                }

                // found the page to delete?
                if (child instanceof TSP_PageView && child.pageProxy.uid === uid)
                {
                    // keep the page name for logging
                    pageName = child.objectName;

                    // get the page index to delete
                    index = i;

                    break;
                }
            }

            // found the page to delete?
            if (index < 0)
            {
                if (verbose)
                    console.log("Remove page - FAILED - view not found");

                return;
            }

            // delete page
            lmPageStack.remove(index);

            // log deleted page
            if (verbose && pageName && pageName.length)
                console.log("Remove page - view was removed - name - " + pageName);

            if (verbose)
                console.log("Remove page - succeeded");
        }
        catch (e)
        {
            console.exception("Remove page - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }
    }

    /**
    * Gets the selected page unique identifier
    *@return the selected page unique identifier, empty string if not found or on error
    */
    function getSelectedPageUID()
    {
        try
        {
            // no selected page?
            if (slPageStack.currentIndex < 0 || slPageStack.currentIndex >= rpPageStack.count)
                return "";

            return rpPageStack.itemAt(slPageStack.currentIndex).pageProxy.uid;
        }
        catch (e)
        {
            console.exception("Get selected page UID - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        return "";
    }
}
