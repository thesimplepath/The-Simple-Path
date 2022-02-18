/****************************************************************************
 * ==> TSP_QmlPage ---------------------------------------------------------*
 ****************************************************************************
 * Description:  Qt document page                                           *
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
#include "Core/TSP_Page.h"

// qt classes
#include "TSP_QmlBox.h"
#include "TSP_QmlBoxProxy.h"
#include "TSP_QmlLink.h"
#include "TSP_QmlLinkProxy.h"
#include "TSP_QmlPageProxy.h"
#include "TSP_QmlProxyDictionary.h"

/**
* Qt document page
*@author Jean-Milost Reymond
*/
class TSP_QmlPage : public TSP_Page
{
    public:
        /**
        * Constructor
        *@param pOwner - the page owner
        */
        TSP_QmlPage(TSP_Item* pOwner);

        /**
        * Constructor
        *@param name - the page name
        *@param pOwner - the page owner
        */
        TSP_QmlPage(const std::wstring& name, TSP_Item* pOwner);

        virtual ~TSP_QmlPage();

        /**
        * Gets the page proxy
        *@return the page proxy, nullptr if no proxy
        */
        virtual TSP_QmlPageProxy* GetProxy() const;

        /**
        * Sets the page proxy
        *@param pProxy - the page proxy
        */
        virtual void SetProxy(TSP_QmlPageProxy* pProxy);

        /**
        * Creates a box and adds it in page
        *@param name - box name
        *@param description - box description
        *@param comments - box comments
        *@param x - link x position in pixels, set to default position if -1
        *@param y - link y position in pixels, set to default position if -1
        *@return newly created box
        */
        virtual TSP_Box* CreateAndAddBox(const std::wstring& name,
                                         const std::wstring& description =  L"",
                                         const std::wstring& comments    =  L"",
                                               int           x           = -1,
                                               int           y           = -1);

        /**
        * Creates a link and adds it in page
        *@param name - link name
        *@param description - link description
        *@param comments - link comments
        *@param x - link x position in pixels, set to default position if -1
        *@param y - link y position in pixels, set to default position if -1
        *@return newly created link
        */
        virtual TSP_Link* CreateAndAddLink(const std::wstring& name,
                                           const std::wstring& description =  L"",
                                           const std::wstring& comments    =  L"",
                                                 int           x           = -1,
                                                 int           y           = -1);

        /**
        * Removes a component
        *@param uid - component unique identifier to remove
        */
        virtual void Remove(const std::string& uid);

        /**
        * Removes a component
        *@param pComponent - component to remove
        */
        virtual void Remove(TSP_Component* pComponent);

        /**
        * Creates a new box view and adds it to the user interface
        *@param pBox - box for which the view should be added
        *@param pPageProxy - the page proxy in which the box view should be created
        *@param type - box type to create
        *@param x - box x position in pixels
        *@param y - box y position in pixels
        */
        template <class T>
        bool CreateBoxView(T* pBox, const QString& type, int x, int y);

    private:
        TSP_QmlPageProxy* m_pProxy = nullptr;
};

//---------------------------------------------------------------------------
// TSP_QmlPage
//---------------------------------------------------------------------------
template <class T>
bool TSP_QmlPage::CreateBoxView(T* pBox, const QString& type, int x, int y)
{
    if (!pBox)
        return false;

    if (!m_pProxy)
        return false;

    // get box unique identifier
    const std::string uid = pBox->GetUID();

    // define the box position type
    TSP_QmlPageProxy::IEBoxPosition boxPos = TSP_QmlPageProxy::IEBoxPosition::IE_BP_Default;

    // do use a custom position?
    if (x > 0 && y > 0)
        boxPos = TSP_QmlPageProxy::IEBoxPosition::IE_BP_Custom;

    // notify page proxy that a new box should be added
    if (!m_pProxy->AddBox(type, QString::fromStdString(pBox->GetUID()), boxPos, x, y))
        return false;

    // get the newly added component proxy
    TSP_QmlBoxProxy* pProxy = static_cast<TSP_QmlBoxProxy*>(TSP_QmlProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the box and its proxy
    pBox->SetProxy(pProxy);
    pProxy->SetBox(pBox);

    return true;
}
//---------------------------------------------------------------------------