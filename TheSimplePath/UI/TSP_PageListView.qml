import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Page list view
*@author JMR
*/
T.Frame
{
    // declared properties
    property string m_PageURL:               "qrc:/Resources/Images/Page.svg"
    property int    m_DefTransitionDuration: 0
    property int    m_TransitionDuration:    0

    // common properties
    id: frPageListViewFrame
    objectName: "frPageListViewFrame"

    /**
    * Page list view background
    */
    Rectangle
    {
        // common properties
        id: rcPageListViewBg
        objectName: "rcPageListViewBg"
        anchors.fill: parent

        /**
        * Page list buttons
        */
        Rectangle
        {
            // common properties
            id: rcPageListViewButtons
            objectName: "rcPageListViewButtons"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            height: 26
            color: "#f0f0f0"

            /**
            * Add page button
            */
            RoundButton
            {
                // common properties
                id: btAddPage
                objectName: "btAddPage"
                anchors.right: btDeletePage.left
                anchors.rightMargin: 3
                anchors.verticalCenter: parent.verticalCenter
                width: 20
                height: 20
                radius: 3
                text: "+"

                /// called when button is clicked
                onClicked:
                {
                    if (tspPageListModel)
                        tspPageListModel.onAddPageClicked();
                }
            }

            /**
            * Delete page button
            */
            RoundButton
            {
                // common properties
                id: btDeletePage
                objectName: "btDeletePage"
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.verticalCenter: parent.verticalCenter
                width: 20
                height: 20
                radius: 3
                text: "-"

                /// called when button is clicked
                onClicked:
                {
                    if (tspPageListModel)
                        tspPageListModel.onDeletePageClicked();
                }
            }
        }

        /**
        * Page list view item
        */
        Component
        {
            // common properties
            id: cpPageItemDelegate

            /**
            * Item content
            */
            Item
            {
                // common properties
                id: itPageViewItem
                objectName: "itPageViewItem"
                width: lvPageListView.width
                height: lvPageListView.m_ItemHeight

                /**
                * Item background
                */
                Rectangle
                {
                    // common properties
                    id: rcPageViewItemBg
                    objectName: "rcPageViewItemBg"
                    anchors.fill: parent
                    color: "transparent"

                    /**
                    * Item glyph
                    */
                    Image
                    {
                        // common properties
                        id: imPageItemGlyph
                        objectName: "imPageItemGlyph"
                        width: lvPageListView.m_ItemHeight
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.margins: 5
                        source: m_PageURL
                        sourceSize: Qt.size(lvPageListView.m_ItemHeight, lvPageListView.m_ItemHeight)
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                    }

                    /**
                    * Item text
                    */
                    Text
                    {
                        // common properties
                        id: txPageViewItemText
                        objectName: "txPageViewItemText"
                        text: tspPageListModel.getPageName(index)
                        anchors.left: imPageItemGlyph.right
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.margins: 5
                        font.family: Styles.m_FontFamily
                        font.pointSize: 9
                        verticalAlignment: Text.AlignVCenter
                        color: Styles.m_DarkTextColor
                        clip: true
                    }
                }

                /**
                * Item mouse area
                */
                MouseArea
                {
                    // common properties
                    id: maPageViewItemMouseArea
                    objectName: "maPageViewItemMouseArea"
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton

                    /// called when item is clicked
                    onClicked:
                    {
                        // get the highlight move time and duration time from page view
                        const moveTime     = (Math.abs(lvPageListView.currentIndex - index) * lvPageListView.m_ItemHeight * 1000) / lvPageListView.highlightMoveVelocity;
                        const durationTime = lvPageListView.highlightMoveDuration > 0 ? lvPageListView.highlightMoveDuration : 0;

                        // calculate the next duration time
                        m_TransitionDuration = (durationTime > 0 && durationTime >= moveTime) ? durationTime : moveTime;

                        // select this item
                        lvPageListView.currentIndex = index;
                    }
                }

                /**
                * Component state array
                */
                states:
                [
                    State
                    {
                        name: "HIGHLIGHTED"
                        when: index === lvPageListView.currentIndex
                        PropertyChanges {target: txPageViewItemText; color: Styles.m_LightTextColor}
                    }
                ]

                /**
                * Transitions between states
                */
                transitions:
                [
                    Transition
                    {
                        from: "*"; to: ""
                        ColorAnimation {property: "color"; easing.type: Easing.Linear; duration: m_DefTransitionDuration}
                    },
                    Transition
                    {
                        from: "*"; to: "HIGHLIGHTED"
                        ColorAnimation {property: "color"; easing.type: Easing.Linear; duration: m_TransitionDuration}
                    }
                ]
            }
        }

        /**
        * Page list view highlight
        */
        Component
        {
            // common properties
            id: cpPageHighlightItemDelegate

            /**
            * Highlight content
            */
            Item
            {
                // common properties
                id: itPageHighlightItem
                objectName: "itPageHighlightItem"
                width: lvPageListView.width
                height: lvPageListView.m_ItemHeight

                /**
                * Highlight background
                */
                Rectangle
                {
                    // common properties
                    id: rcPageHighlightItemBg
                    objectName: "rcPageHighlightItemBg"
                    anchors.fill: parent
                    color: Styles.m_HighlightColor
                }
            }
        }

        /**
        * Page list view
        */
        ListView
        {
            // declared properties
            property int m_ItemHeight: 25

            // common properties
            id: lvPageListView
            objectName: "lvPageListView"
            anchors.left: parent.left
            anchors.top: rcPageListViewButtons.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            focus: true
            clip: true

            // link properties
            model: tspPageListModel
            delegate: cpPageItemDelegate
            highlight: cpPageHighlightItemDelegate

            /**
            * Vertical scrollbar
            */
            ScrollBar.vertical: ScrollBar
            {
                // common properties
                id: sbPageListView
                objectName: "sbPageListView"
                parent: lvPageListView
                visible: true
                minimumSize: 0.1
            }
        }

        /**
        * Bind signals from the c++ model to the view
        */
        /*REM
        //REM ?
        Connections
        {
            // common properties
            target: tspPageListModel
            */

            /*REM
            function onTestSignal()
            {
                console.log("+++++ +++++ This signal responded!!!");
            }
            */

            /**
            * Called when a row is inserted
            *@param {QModelIndex} parentIndex - parent index which will own the row(s) to insert
            *@param {QModelIndex} first - first added row index
            *@param {QModelIndex} last - last added row index
            */
            /*REM
            function onRowsInserted(parentIndex, first, last)
            {
                //REM lvPageListView.append({text: "New page 1"})
            }
        }
        */
    }
}
