/****************************************************************************
 * ==> TSP_QmlAtlasPage ----------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document page owned by an atlas                         *
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

// std
#include <vector>

// core classes
#include "Core/TSP_Process.h"

// qt classes
#include "TSP_QmlAtlas.h"
#include "TSP_QmlPage.h"
#include "TSP_QmlPageProxy.h"

// class prototype
class TSP_QmlProcess;

/**
* Qt document page owned by an atlas
*@author Jean-Milost Reymond
*/
class TSP_QmlAtlasPage : public TSP_QmlPage
{
    public:
        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_QmlAtlasPage(TSP_QmlAtlas* pOwner);

        /**
        * Constructor
        *@param name - the page name
        *@param pOwner - the page owner
        */
        TSP_QmlAtlasPage(const std::wstring& name, TSP_QmlAtlas* pOwner);

        virtual ~TSP_QmlAtlasPage();

        /**
        * Creates a process and adds it in page
        *@param name - process name
        *@param description - process description
        *@param comments - process comments
        *@param x - process x position in pixels, set to default position if -1
        *@param y - process y position in pixels, set to default position if -1
        *@param width - process width in pixels, set to default width if -1
        *@param height - process height in pixels, set to default width if -1
        *@return newly created process
        */
        virtual TSP_Process* CreateAndAddProcess(const std::wstring& name,
                                                 const std::wstring& description =  L"",
                                                 const std::wstring& comments    =  L"",
                                                       int           x           = -1,
                                                       int           y           = -1,
                                                       int           width       = -1,
                                                       int           height      = -1);
};
