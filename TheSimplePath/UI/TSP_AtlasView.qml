import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Templates 2.15 as T

// c++
import thesimplepath.proxys 1.0

/**
* Document atlas view
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias atlasProxy: apAtlasProxy

    // advanced properties
    property var m_Atlas: this

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

        /// Called when a page should be added to the atlas view
        onAddPageToView: function(uid)
        {
            // add a page to the pages view, and show it immediately
            const page = pvPagesView.addPage(uid, true);

            // notify if the page was added successfully
            onPageAdded(page);
        }

        /// Called when a page should be remove from the atlas view
        onRemovePageFromView: function(uid)
        {
            pvPagesView.removePage(uid, true);
        }

        /// Called when the selected page unique identifier was queried
        onQuerySelectedPageUID: function()
        {
            onSelectedPageUIDQueried(pvPagesView.getSelectedPageUID());
        }

        /// Called when the selected page owner unique identifier is queried
        onQuerySelectedPageOwnerUID: function()
        {
            onSelectedPageOwnerUIDQueried(tspPageListModel.queryPageOwnerUID());
        }
    }

    /**
    * Pages view
    *@note This view contains all the pages shown in the document, i.e. the pages
    *      which are belonging to an atlas, as well as the pages which are belonging
    *      to a process, which is itself the child of an atlas page. This was performed
    *      this way because a process cannot show a page content directly, only the
    *      pages view located on the currently opened atlas can achieve that. For that
    *      reason the pages view doesn't respect exactly the view hierarchy
    */
    TSP_PagesView
    {
        // common properties
        id: pvPagesView
        objectName: "pvPagesView"
        anchors.fill: parent
    }
}
