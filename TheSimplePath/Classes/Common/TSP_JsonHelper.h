/****************************************************************************
 * ==> TSP_JsonHelper ------------------------------------------------------*
 ****************************************************************************
 * Description:  Json helper                                                *
 * Contained in: Common                                                     *
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

 // rapid json
#include "rapidjson/encodings.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
//REM #include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

/**
* Json helper
*@author Jean-Milost Reymond
*/
class TSP_JsonHelper
{
    public:
        typedef rapidjson::Document                                                         IDocument;
        typedef rapidjson::GenericDocument<rapidjson::UTF16<>>                              IDocumentW;
        typedef rapidjson::Value                                                            IValue;
        typedef rapidjson::GenericValue<rapidjson::UTF16<>>                                 IValueW;
        typedef rapidjson::StringBuffer                                                     IStringBuffer;
        typedef rapidjson::GenericStringBuffer<rapidjson::UTF16<>, rapidjson::CrtAllocator> IStringBufferW;
        typedef rapidjson::Writer<IStringBuffer>                                            IStringBufferWriter;
        typedef rapidjson::Writer<IStringBufferW, rapidjson::UTF16<>, rapidjson::UTF16<>>   IStringBufferWriterW;
        typedef rapidjson::GenericStringRef<wchar_t>                                        IStringRefW;

        /**
        * Constructor
        */
        TSP_JsonHelper();

        /**
        * Destructor
        */
        virtual ~TSP_JsonHelper();
};
