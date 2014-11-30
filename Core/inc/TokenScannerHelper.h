////////////////////////////////////////////////////////////
/** @file TokenScannerHelper.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 28/11/2014
 *
 *  Defines the TokenScannerHelper class.
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
        bool isWhiteSpace(char character);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if given character is contained in 
         *  given Array.
         *  @param character : Character to test.
         *  @param array : Array to look in.
         **/
        /////////////////////////////////////////////////////////////
        bool isEquals(char character, const CharArray& array);
    };
}

#endif
