/****************************************************************************
 * ==> TSP_QmlBox ----------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt box component                                           *
 * Contained in: Qt                                                         *
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

#pragma once

// core classes
#include "Core\TSP_Box.h"
#include "Core\TSP_Page.h"

// qt classes
#include "TSP_QmlBoxProxy.h"

/**
* Qt box component
*@author Jean-Milost Reymond
*/
class TSP_QmlBox : public TSP_Box
{
    public:
        /**
        * Connector position
        *@note This enum is linked with the one located in TSP_Connector.
        *      Don't modify it without updating its twin
        */
        enum class IEPosition
        {
            IE_P_None = 0,
            IE_P_Left,
            IE_P_Top,
            IE_P_Right,
            IE_P_Bottom
        };

        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_QmlBox(TSP_Page* pOwner);

        /**
        * Constructor
        *@param title - component title
        *@param description - component description
        *@param comments - component comments
        *@param pOwner - component owner
        */
        TSP_QmlBox(const std::wstring& title,
                   const std::wstring& description,
                   const std::wstring& comments,
                         TSP_Page*     pOwner);

        virtual ~TSP_QmlBox();

        /**
        * Gets the box proxy
        *@return the box proxy, nullptr if no proxy
        */
        TSP_QmlBoxProxy* GetProxy() const;

        /**
        * Sets the box proxy
        *@param pProxy - the box proxy
        */
        void SetProxy(TSP_QmlBoxProxy* pProxy);

    private:
        TSP_QmlBoxProxy* m_pProxy = nullptr;
};
