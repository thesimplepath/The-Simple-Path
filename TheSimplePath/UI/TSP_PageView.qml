import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Document page view
*@author Jean-Milost Reymond
*/
TSP_Page
{
    // properties
    property string m_Type: "TSP_PageView"

    // advanced properties
    m_PageWidth:  m_MainFormModel.getPageWidth()
    m_PageHeight: m_MainFormModel.getPageHeight()

    /// Called when a new box view should be added to page
    onDoAddBox: function(type, uid, position, x, y, width, height)
    {
        // search for symbol type to create
        switch (type)
        {
            case "":
            case "process":
            {
                // calculate the process position
                const [xPos, yPos] = getBoxPosition(position, x, y, width, height);

                let process;

                // add a process to the page
                if (width === -1 || height === -1)
                    process = addProcessDefSize(xPos, yPos, uid);
                else
                    process = addProcess(xPos, yPos, width, height, uid);

                // notify if the box was added successfully
                pageProxy.onBoxAdded(process);

                return;
            }
        }
    }

    /// Called when a new link view should be added to page
    onDoAddLink: function(type, uid, startUID, startPos, endUID, endPos, x, y, width, height)
    {}

    /**
    * Adds a start component to the document, with a default size
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    */
    function addStartDefSize(x, y)
    {
        return addStart(x,
                        y,
                        m_PageWidth  * 0.18,
                        m_PageHeight * 0.082);
    }

    /**
    * Adds a start component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    */
    function addStart(x, y, width, height)
    {
        return addSymbol("start",
                         x,
                         y,
                         width,
                         height,
                         false,
                         false,
                         false,
                         true);
    }

    /**
    * Adds an end component to the document, with a default size
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    */
    function addEndDefSize(x, y)
    {
        return addEnd(x,
                      y,
                      m_PageWidth  * 0.18,
                      m_PageHeight * 0.082);
    }

    /**
    * Adds an end component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    */
    function addEnd(x, y, width, height)
    {
        return addSymbol("end",
                         x,
                         y,
                         width,
                         height,
                         false,
                         true,
                         false,
                         false);
    }

    /**
    * Adds a process component to the document, with a default size
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {string} uid - process unique identifier
    */
    function addProcessDefSize(x, y, uid)
    {
        return addProcess(x,
                          y,
                          m_PageWidth  * 0.18,
                          m_PageHeight * 0.082,
                          uid);
    }

    /**
    * Adds a process component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    *@param {string} uid - process unique identifier
    */
    function addProcess(x, y, width, height, uid)
    {
        return addSymbol("process",
                         x,
                         y,
                         width,
                         height,
                         false,
                         false,
                         false,
                         false,
                         uid);
    }

    /**
    * Adds an activity component to the document, with a default size
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    */
    function addActivityDefSize(x, y)
    {
        return addActivity(x,
                           y,
                           m_PageWidth  * 0.18,
                           m_PageHeight * 0.082);
    }

    /**
    * Adds an activity component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    */
    function addActivity(x, y, width, height)
    {
        return addSymbol("activity",
                         x,
                         y,
                         width,
                         height,
                         true,
                         true,
                         true,
                         true);
    }

    /**
    * Adds a page break component to the document, with a default size
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {bool} isProcess - if true, the page break links to a process instead of a page
    *@param {bool} isExit - if true, the page break is an exit instead of an input
    */
    function addPageBreakDefSize(x, y, isProcess, isExit)
    {
        return addPageBreak(x,
                            y,
                            m_PageWidth  * 0.11,
                            m_PageHeight * 0.06,
                            isProcess,
                            isExit);
    }

    /**
    * Adds a page break component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    *@param {bool} isProcess - if true, the page break links to a process instead of a page
    *@param {bool} isExit - if true, the page break is an exit instead of an input
    */
    function addPageBreak(x, y, width, height, isProcess, isExit)
    {
        let symbol = addSymbol("pageBreak",
                               x,
                               y,
                               width,
                               height,
                               false,
                               !isProcess && !isExit,
                               false,
                               !isProcess && isExit);

        if (!symbol)
            return undefined;

        symbol.m_IsProcess = isProcess;
        symbol.m_IsExit    = isExit;

        return symbol;
    }

    /**
    * Adds a symbol component to the document
    *@param {number} x - component x position, in pixels
    *@param {number} y - component y position, in pixels
    *@param {number} width - component width, in pixels
    *@param {number} height - component height, in pixels
    *@param {bool} leftConnVisible - if true, the left connector is visible on the symbol
    *@param {bool} topConnVisible - if true, the top connector is visible on the symbol
    *@param {bool} rightConnVisible - if true, the right connector is visible on the symbol
    *@param {bool} bottomConnVisible - if true, the bottom connector is visible on the symbol
    *@param {string} uid - process unique identifier
    */
    function addSymbol(name,
                       x,
                       y,
                       width,
                       height,
                       leftConnVisible,
                       topConnVisible,
                       rightConnVisible,
                       bottomConnVisible,
                       uid)
    {
        let componentName;

        // get component name to load
        switch (name)
        {
            case "start":     componentName = "TSP_Start.qml";     break;
            case "end":       componentName = "TSP_End.qml";       break;
            case "procedure": componentName = "TSP_Procedure.qml"; break;
            case "process":   componentName = "TSP_Process.qml";   break;
            case "activity":  componentName = "TSP_Activity.qml";  break;
            case "pageBreak": componentName = "TSP_PageBreak.qml"; break;

            default:
            {
                console.error("Add symbol - unknown component name - " + name);
                return;
            }
        }

        // load the component
        let component = Qt.createComponent(componentName);

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add symbol - an error occurred while the component was created - name - " +
                          name                                                                       +
                          " - "                                                                      +
                          component.errorString());
            return;
        }

        const connectorWidth  = Styles.m_ConnectorWidth;
        const connectorHeight = Styles.m_ConnectorHeight;

        // build symbol identifier
        const symbolId = "bxSymbol_" + uid;

        // create and show new item object
        let item = component.createObject(pageContent, {"id":                      symbolId,
                                                        "objectName":              symbolId,
                                                        "x":                       x,
                                                        "y":                       y,
                                                        "width":                   width,
                                                        "height":                  height,
                                                        "m_ScaleFactor":           m_ScaleFactor,
                                                        "leftConnector.x":        -((connectorWidth  / 2) + 2),
                                                        "topConnector.y":         -((connectorHeight / 2) + 2),
                                                        "rightConnector.x":        width  + 2 - (connectorWidth  / 2),
                                                        "bottomConnector.y":       height + 2 - (connectorHeight / 2),
                                                        "leftConnector.visible":   leftConnVisible,
                                                        "topConnector.visible":    topConnVisible,
                                                        "rightConnector.visible":  rightConnVisible,
                                                        "bottomConnector.visible": bottomConnVisible});

        // succeeded?
        if (!item)
        {
            console.error("Add symbol - an error occurred while the symbol was added to page");
            return undefined;
        }

        // declare the unique identifier in the symbol proxy
        item.boxProxy.uid = uid;

        console.log("Add symbol - succeeded - name - " + name + " - id - " + item.objectName);

        return item;
    }

    /**
    * Adds a message component to the document
    *@param {TSP_Connector} from - connector belonging to symbol the message is attached from
    *@param {TSP_Connector} to - connector belonging to symbol the message is attached to, if undefined the message is dragging
    */
    function addMessage(from, to)
    {
        // load the item component
        let component = Qt.createComponent('TSP_Message.qml');

        // succeeded?
        if (component.status !== Component.Ready)
        {
            console.error("Add message - an error occurred while the component was created - " + component.errorString());
            return;
        }

        // create and show new item object
        let item = component.createObject(pageContent, {"id":            "mgMessage" + m_GenIndex,
                                                        "objectName":    "mgMessage" + m_GenIndex,
                                                        "m_From":        from,
                                                        "m_To":          to,
                                                        "m_ScaleFactor": m_ScaleFactor,
                                                        "m_LabelSize.x": m_PageWidth  * 0.17,
                                                        "m_LabelSize.y": m_PageHeight * 0.067});

        console.log("Add message - succeeded - new item - " + item.objectName);

        ++m_GenIndex; // REM FIXME

        /*REM FIXME
        // notify page model that a message was added
        if (pvPageView.m_Model)
            pvPageView.m_Model.onMessageAdded(pvPageView.m_UID, item.m_UID);
        */

        return item;
    }

    /**
    * Called when starting to add a link
    *@param {TSP_Connector} from - connector belonging to box the link starts from
    *@return {TSP_Link} added link, undefined on error
    */
    /*FIXME RE-ENABLE WHEN READY
    function startAddLink(from)
    {
        return addMessage(from, undefined);
    }
    */

    /*REM
    /// called when page is loaded
    Component.onCompleted:
    {
    / *REM
        let start = addStartDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200,  50);
        let activity = addActivityDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200, 250);
        let end = addEndDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "ID : 19353", "<i>Gestionnaires de fortune accrédités</i>", 200, 450);
        let process = addProcessDefSize("<b>Rechercher les antécédents de Décès attendus</b>", "", "", 400, 200);
        let pageBreak = addPageBreakDefSize("Page des cas spéciaux", "", "", 400, 400, false, false);
        let pageBreak2 = addPageBreakDefSize("Page des cas spéciaux", "", "", 550, 400, false, true);
        let pageBreak3 = addPageBreakDefSize("Page des cas spéciaux", "", "", 400, 500, true, false);
        let pageBreak4 = addPageBreakDefSize("Page des cas spéciaux", "", "", 550, 500, true, true);
        addMessage("Demande de tarification exceptionnelle à suivre rapidement", "ID : 5940", "<i>45%</i>", start.bottomConnector, activity.topConnector);
        addMessage("Demande de tarification exceptionnelle à suivre rapidement", "ID : 5940", "<i>45%</i>", activity.bottomConnector, end.topConnector);
        * /
        let start = addStartDefSize(200,  50);
        let activity = addActivityDefSize(200, 250);
        let end = addEndDefSize(200, 450);
        let process = addProcessDefSize(400, 200);
        let pageBreak = addPageBreakDefSize(400, 400, false, false);
        let pageBreak2 = addPageBreakDefSize(550, 400, false, true);
        let pageBreak3 = addPageBreakDefSize(400, 500, true, false);
        let pageBreak4 = addPageBreakDefSize(550, 500, true, true);
        addMessage(start.bottomConnector, activity.topConnector);
        addMessage(activity.bottomConnector, end.topConnector);
    }
    */
}
