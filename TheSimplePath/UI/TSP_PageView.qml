import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Document page view
*@author Jean-Milost Reymond
*/
TSP_Page
{
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
    *@param {string} name - symbol file name to load
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
        try
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

            // build symbol loader identifier
            const loaderId = "ldSymbol_" + uid;

            // create a loader to load the symbol
            pageContentModel.append({"id": loaderId, "loaderId": loaderId, "isBox": true});

            // get the newly added loader
            let loader = pageContentRepeater.itemAt(pageContentRepeater.count - 1);

            // found it?
            if (!loader)
            {
                console.error("Add symbol - an error occurred while the loader was created");
                return undefined;
            }

            const connectorWidth  = Styles.m_ConnectorWidth;
            const connectorHeight = Styles.m_ConnectorHeight;

            // build symbol identifier
            const symbolId = "bxSymbol_" + uid;

            // load the symbol
            loader.setSource(componentName, {
                "id":                      symbolId,
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
                "bottomConnector.visible": bottomConnVisible,
                "m_PageContent":           pageContent,
                "boxProxy.uid":            uid
            });

            // get the loaded symbol
            let symbol = loader.item;

            // found it?
            if (!symbol || symbol.boxProxy.uid !== uid)
            {
                console.error("Add symbol - an error occurred while the item was created");
                return undefined;
            }

            console.log("Add symbol - succeeded - name - " + name + " - id - " + symbol.objectName);

            return symbol;
        }
        catch (e)
        {
            console.exception("Add symbol - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // remove the partially added symbol, if any
        removeComponent(uid);

        return undefined;
    }

    /**
    * Adds a message component to the document
    *@param {TSP_Connector} from - connector belonging to symbol the message is attached from
    *@param {TSP_Connector} to - connector belonging to symbol the message is attached to, if undefined the message is dragging
    *@param {number} x - label x position, in pixels
    *@param {number} y - label y position, in pixels
    *@param {number} width - label width, in pixels
    *@param {number} height - label height, in pixels
    *@param {string} uid - link unique identifier
    *@return {TSP_Message} added message, undefined on error
    */
    function addMessage(from, to, x, y, width, height, uid)
    {
        try
        {
            // build message loader identifier
            const loaderId = "ldMessage_" + uid;

            // create a loader to load the message
            pageContentModel.append({"id": loaderId, "loaderId": loaderId, "isBox": false});

            // get the newly added loader
            let loader = pageContentRepeater.itemAt(pageContentRepeater.count - 1);

            // found it?
            if (!loader)
            {
                console.error("Add message - an error occurred while the loader was created");
                return undefined;
            }

            // build message identifier
            const messageId = "mgMessage_" + uid;

            // load the message
            loader.setSource("TSP_Message.qml", {
                "id":            messageId,
                "objectName":    messageId,
                "m_From":        from,
                "m_To":          to,
                "m_ScaleFactor": m_ScaleFactor,
                "m_LabelSize.x": m_PageWidth  * 0.17,
                "m_LabelSize.y": m_PageHeight * 0.067,
                "m_PageContent": pageContent,
                "linkProxy.uid": uid
            });

            // get the loaded link
            let message = loader.item;

            // found it?
            if (!message || message.linkProxy.uid !== uid)
            {
                console.error("Add message - an error occurred while the item was created");
                return undefined;
            }

            // set the label position, if defined
            if (x >= 0 && y >= 0)
                message.m_LabelPos = Qt.vector2d(x, y);

            // set the label size, if defined
            if (width >= 0 && height >= 0)
                message.m_LabelSize = Qt.vector2d(width, height);

            // emit signal and log only if destination connector is defined
            if (to)
            {
                // emit signal that message was added
                linkAdded(message);

                console.log("Add message - succeeded - new item - " + message.objectName);
            }

            return message;
        }
        catch (e)
        {
            console.exception("Add message - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // remove the partially added message, if any
        removeComponent(uid);

        return undefined;
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
}
