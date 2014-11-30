////////////////////////////////////////////////////////////
/** @file TokenScannerHelper.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 28/11/2014
 *
 *  Implements the TokenScannerHelper class.
 *
 **/
////////////////////////////////////////////////////////////
#include "TokenScannerHelper.h"

namespace APro
{
    bool TokenScannerHelper::isAlpha (char character)
    {
        return (character >= 'a' && character <= 'z') ||
               (character >= 'A' && character <= 'Z');
    }
    
    bool TokenScannerHelper::isNum (char character)
    {
        return character >= '0' && character <= '9';
    }
    
    bool TokenScannerHelper::isAlphaNum (char character)
    {
        return TokenScannerHelper::isAlpha (character) ||
               TokenScannerHelper::isNum (character);
    }
    
    bool TokenScannerHelper::isQuote (char character)
    {
        return character == '"' || character == '\'';
    }
    
    bool TokenScannerHelper::isOperator (char character)
    {
        return character == '[' || character == ']' ||
               character == '{' || character == '}' ||
               character == '(' || character == ')' ||
               character == ',' || character == '|' ||
               character == '=' || character == ':' ||
               character == ';' || character == '?';
    }
    
    bool TokenScannerHelper::isWhiteSpace (char character)
    {
        return character == ' '  || character == '\t' ||
               character == '\r' || character == '\n';
    }
    
    bool TokenScannerHelper::isEquals (char character, const CharArray& array)
    {
        return array.find(character) != array.end();
    }
}