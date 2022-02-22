/****************************************************************************
 * ==> TSP_JSHelper --------------------------------------------------------*
 ****************************************************************************
 * Description:  Javascript helper functions                                *
 * Contained in: Component                                                  *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - The Simple Path                                            *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

/**
* Clamps a value in a range
*@param {number} value - value to clamp
*@param {number} min - min range value
*@param {number} max - max range value
*/
function clamp(value, min, max)
{
    return Math.min(Math.max(value, min), max);
}

/**
* Clamps a value in a range between 0.0 and 1.0
*@param {number} value - value to clamp
*/
function clamp01(value)
{
    return clamp(value, 0.0, 1.0);
}

/**
* Sleeps during a time
*@param {number} milliseconds - sleep time in milliseconds
*/
function sleep(milliseconds) {
    const date    = new Date();
    var   curDate = undefined;

    do
    {
        curDate = new Date();
    }
    while (curDate - date < milliseconds);
}

/**
* Logs all the children contained in an item
*@param {item} item - start item from which the children should be logged
*@note Start item will also be logged
*/
function logAllChildren(item)
{
    // iterate through children
    for (let i = 0; i < item.children.length; ++i)
        logAllChildren(item.children[i]);

    // log child name
    console.log("Child - name - " + item.objectName);
}

/**
* Finds the items below a point
*@param {item} item - start item from which the children should be logged
*@param {point} point - point above which the items should be found
*@param {array} result - found items
*@note Start item will also be checked
*/
function getItemsAbovePoint(item, point, result)
{
    // iterate through children
    for (let i = 0; i < item.children.length; ++i)
        getItemsAbovePoint(item.children[i], point, result);

    // item contains point?
    if (item.contains(item.mapFromGlobal(point.x, point.y)))
        result.push(item);
}
