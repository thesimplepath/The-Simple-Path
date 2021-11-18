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
function clamp01(value, min, max)
{
    return clamp(value, 0.0, 1.0);
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