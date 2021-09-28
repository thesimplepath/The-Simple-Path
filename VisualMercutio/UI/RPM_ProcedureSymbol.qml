import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Procedure symbol
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Symbol mode
    */
    enum IEMode
    {
        IE_M_Default,
        IE_M_MoveSize,
        IE_M_Edit
    }

    // common properties
    id: hcProcedureSymbol

    /**
    * Symbol background, also handles gesture
    */
    RPM_HandlesControl
    {
        // common properties
        id: hcBackground
        anchors.fill: parent
        z: -1

        // advanced properties
        m_HandleVisible: false
        m_Target: hcProcedureSymbol

        /**
        * Called when the move and size mode should be disabled
        */
        function doDisableMoveSize()
        {
            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Edit);
            edFirstLine.edit.forceActiveFocus();
        }
    }

    /**
    * Symbol content
    */
    Rectangle
    {
        // common properties
        id: rcContent
        anchors.fill: parent
        color: "transparent"
        border.color: "#202020"
        border.width: 1
        radius: 3
        z: 0

        /**
        * Splitted view
        */
        SplitView
        {
            // common properties
            id: svSymbolView
            anchors.fill: parent
            orientation: Qt.Vertical

            /**
            * Splitter handle
            */
            handle: Rectangle
            {
                // common properties
                implicitWidth: parent.width
                implicitHeight: 1
                color: SplitHandle.pressed ? "#a0a0a0" : (SplitHandle.hovered ? "#808080" : "#202020")
            }

            /**
            * First area
            */
            Rectangle
            {
                // common properties
                SplitView.preferredWidth: hcProcedureSymbol.width
                SplitView.preferredHeight: hcProcedureSymbol.height / 3
                SplitView.minimumHeight: 10
                color: "transparent"

                /**
                * First area text edit
                */
                RPM_Edit
                {
                    // common properties
                    id: edFirstLine
                    anchors.fill: parent
                    edit.objectName: "edFirstLine"

                    /**
                    * Called when the active focus changed
                    *@param hasFocus - if true, the edit has the focus
                    */
                    function activeFocusChanged(hasFocus)
                    {
                        // editors are no longer focused?
                        if (!hasFocus && !edSecondLine.edit.activeFocus && !edThirdLine.edit.activeFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when the editing has finished
                    */
                    function editingFinished()
                    {
                        // editors are no longer focused?
                        if (!edit.activeFocus && !edSecondLine.edit.activeFocus && !edThirdLine.edit.activeFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when previous edit should be selected
                    */
                    function doSelectPrevEdit()
                    {
                        edThirdLine.edit.forceActiveFocus();
                    }

                    /**
                    * Called when next edit should be selected
                    */
                    function doSelectNextEdit()
                    {
                        edSecondLine.edit.forceActiveFocus();
                    }
                }
            }

            /**
            * Second area
            */
            Rectangle
            {
                // common properties
                SplitView.preferredWidth: hcProcedureSymbol.width
                SplitView.preferredHeight: hcProcedureSymbol.height / 3
                SplitView.minimumHeight: 10
                SplitView.fillHeight: true
                color: "transparent"

                /**
                * Second area text edit
                */
                RPM_Edit
                {
                    // common properties
                    id: edSecondLine
                    anchors.fill: parent
                    edit.objectName: "edSecondLine"

                    /**
                    * Called when the active focus changed
                    *@param hasFocus - if true, the edit has the focus
                    */
                    function activeFocusChanged(hasFocus)
                    {
                        // editors are no longer focused?
                        if (!edFirstLine.edit.activeFocus && !hasFocus && !edThirdLine.edit.activeFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when the editing has finished
                    */
                    function editingFinished()
                    {
                        // editors are no longer focused?
                        if (!edFirstLine.edit.activeFocus && !activeFocus && !edThirdLine.edit.activeFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when previous edit should be selected
                    */
                    function doSelectPrevEdit()
                    {
                        edFirstLine.edit.forceActiveFocus();
                    }

                    /**
                    * Called when next edit should be selected
                    */
                    function doSelectNextEdit()
                    {
                        edThirdLine.edit.forceActiveFocus();
                    }
                }
            }

            /**
            * Third area
            */
            Rectangle
            {
                // common properties
                SplitView.preferredWidth: hcProcedureSymbol.width
                SplitView.preferredHeight: hcProcedureSymbol.height / 3
                SplitView.minimumHeight: 10
                color: "transparent"

                /**
                * Third area text edit
                */
                RPM_Edit
                {
                    // common properties
                    id: edThirdLine
                    anchors.fill: parent
                    edit.objectName: "edThirdLine"

                    /**
                    * Called when the active focus changed
                    *@param hasFocus - if true, the edit has the focus
                    */
                    function activeFocusChanged(hasFocus)
                    {
                        // editors are no longer focused?
                        if (!edFirstLine.edit.activeFocus && !edSecondLine.edit.activeFocus && !hasFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when the editing has finished
                    */
                    function editingFinished()
                    {
                        // editors are no longer focused?
                        if (!edFirstLine.edit.activeFocus && !edSecondLine.edit.activeFocus && !activeFocus)
                            setMode(RPM_ProcedureSymbol.IEMode.IE_M_Default);
                    }

                    /**
                    * Called when previous edit should be selected
                    */
                    function doSelectPrevEdit()
                    {
                        edSecondLine.edit.forceActiveFocus();
                    }

                    /**
                    * Called when next edit should be selected
                    */
                    function doSelectNextEdit()
                    {
                        edFirstLine.edit.forceActiveFocus();
                    }
                }
            }
        }

        /**
        * Split view mouse area
        */
        MouseArea
        {
            // common properties
            id: maMouseArea
            anchors.fill: parent

            /// called when the view is clicked
            onClicked:
            {
                setMode(RPM_ProcedureSymbol.IEMode.IE_M_MoveSize);
            }
        }
    }

    /**
    * Set the current symbol mode
    *@param value - if true, move and size mode is enabled, disabled otherwise
    */
    function setMode(mode)
    {
        switch (mode)
        {
            case RPM_ProcedureSymbol.IEMode.IE_M_Default:
                hcBackground.z               = -1;
                hcBackground.m_HandleVisible =  false;
                rcContent.z                  =  0;
                maMouseArea.visible          =  true;
                break;

            case RPM_ProcedureSymbol.IEMode.IE_M_MoveSize:
                hcBackground.z               =  0;
                hcBackground.m_HandleVisible =  true;
                rcContent.z                  = -1;
                maMouseArea.visible          =  false;
                break;

            case RPM_ProcedureSymbol.IEMode.IE_M_Edit:
                hcBackground.z               = -1;
                hcBackground.m_HandleVisible =  false;
                rcContent.z                  =  0;
                maMouseArea.visible          =  false;
                break;
        }
    }
}
