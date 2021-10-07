/****************************************************************************
 * ==> TSP_Model -----------------------------------------------------------*
 ****************************************************************************
 * Description:  Resource and process manager business model                *
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

 // std
#include <vector>

// core classes
#include "TSP_Page.h"

/**
* Resource and process manager business model
*@author Jean-Milost Reymond
*/
class TSP_Model
{
    public:
        TSP_Model();

        /**
        * Constructor
        *@param name - model name
        */
        TSP_Model(const std::wstring& name);

        virtual ~TSP_Model();

        /**
        * Gets the model name
        *@return the model name
        */
        virtual inline std::wstring GetName() const;

        /**
        * Sets the model name
        *@param name - the model name
        */
        virtual inline void SetName(const std::wstring& name);

        /**
        * Gets the next available identifier
        *@return next available identifier
        *@note The identifier is unique in the model
        *@note BE CAREFUL calling this function, the internal identifier generator will be incremented by 1
        */
        virtual inline std::size_t GetNextID();

        /**
        * Gets the last (i.e the higher) identifier in the model
        *@return the last (i.e the higher) identifier in the model
        */
        virtual inline std::size_t GetLastID() const;

        /**
        * Loads a model from a file
        *@return true on success, otherwise false
        */
        virtual bool Load();

        /**
        * Saves a model to a file
        *@return true on success, otherwise false
        */
        virtual bool Save() const;

    private:
        typedef std::vector<TSP_Page*> IPages;

        IPages       m_Pages;
        std::wstring m_Name;
        std::size_t  m_NbrGen = 0;
};

//---------------------------------------------------------------------------
// TSP_Model
//---------------------------------------------------------------------------
std::wstring TSP_Model::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void TSP_Model::SetName(const std::wstring& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
std::size_t TSP_Model::GetNextID()
{
    return ++m_NbrGen;
}
//---------------------------------------------------------------------------
std::size_t TSP_Model::GetLastID() const
{
    return m_NbrGen;
}
//---------------------------------------------------------------------------
