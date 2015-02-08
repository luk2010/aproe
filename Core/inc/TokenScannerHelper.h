////////////////////////////////////////////////////////////
/** @file TokenScannerHelper.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 28/11/2014 - 07/02/2015
 *
 *  @brief
 *  Defines the TokenScannerHelper class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
////////////////////////////////////////////////////////////
#ifndef APRO_TOKENSCANNERHELPER_H
#define APRO_TOKENSCANNERHELPER_H

#include "Platform.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class TokenScannerHelper
     *  @ingroup Utils
     *  @brief Helper class for TokenScanner.
    **/
    /////////////////////////////////////////////////////////////
    class TokenScannerHelper
    {
    protected:
        TokenScannerHelper() {}
        ~TokenScannerHelper() {}
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is Alpha.
         *  (a-z, A-Z)
         *  @param character : Character to test.
         **/
        /////////////////////////////////////////////////////////////
        static bool isAlpha(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is Numeric.
         *  (0-9)
         *  @param character : Character to test.
         **/
        /////////////////////////////////////////////////////////////
        static bool isNum(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is Alphanumeric.
         *  (a-z, A-Z, 0-9)
         *  @param character : Character to test.
        **/
        /////////////////////////////////////////////////////////////
        static bool isAlphaNum(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is a Quote.
         *  (",')
         *  @param character : Character to test.
        **/
        /////////////////////////////////////////////////////////////
        static bool isQuote(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is Operator.
         *  ({,},[,],(,),,,|,=,:,;,?)
         *  @note These operators are common used operators.
         *  @param character : Character to test.
        **/
        /////////////////////////////////////////////////////////////
        static bool isOperator(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is a WhiteSpace.
         *  (' ', \t, \n, \r)
         *  @param character : Character to test.
         **/
        /////////////////////////////////////////////////////////////
        static bool isWhiteSpace(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is contained in 
         *  given Array.
         *  @param character : Character to test.
         *  @param array : Array to look in.
         **/
        /////////////////////////////////////////////////////////////
        static bool isEquals(char character, const CharArray& array);
    };
}

#endif
