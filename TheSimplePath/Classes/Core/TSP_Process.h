/****************************************************************************
 * ==> TSP_Process ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Process component                                          *
 * Contained in: Core                                                       *
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
#include "TSP_Box.h"
#include "TSP_Page.h"
#include "TSP_Attribute.h"
#include "TSP_PageContainer.h"

/**
* Process component
*@author Jean-Milost Reymond
*/
class TSP_Process : public TSP_Box,
                    public TSP_PageContainer
{
    public:
        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_Process(TSP_Page* pOwner);

        /**
        * Constructor
        *@param title - component title
        *@param description - component description
        *@param comments - component comments
        *@param pOwner - component owner
        */
        TSP_Process(const std::wstring& title,
                    const std::wstring& description,
                    const std::wstring& comments,
                          TSP_Page*     pOwner);

        virtual ~TSP_Process();

        /**
        * Creates a page
        *@return newly created page
        */
        virtual TSP_Page* CreatePage();

        /**
        * Creates a page
        *@param name - page name
        *@return newly created page
        */
        virtual TSP_Page* CreatePage(const std::wstring& name);
};
