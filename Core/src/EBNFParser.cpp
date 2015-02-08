////////////////////////////////////////////////////////////
/** @file EBNFParser.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 13/11/2014 - 07/02/2015
 *
 *  @brief
 *  Implements the EBNFParser class.
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
#include "EBNFParser.h"
#include "TokenScannerHelper.h"

namespace APro
{
    namespace EBNF
    {
        void EBNFScanner::nextToken()
        {
            if(currentToken > -1 && currentToken < tokens.size() - 1)
            {
                currentToken++;
                return;
            }
            
            while (hasNextCharacter())
            {
                nextCharacter();
                
                // Scan the Identifier type. [a-zA-Z\-_]
                if(TokenScannerHelper::isAlpha(currentCharacter))
                {
                    Token tok = scanIdentifier();
                    tokens.append(std::move(tok));
                    currentToken++;
                    return;
                }
                
                // Scan a literal
                else if (TokenScannerHelper::isQuote(currentCharacter))
                {
                    Token tok = scanLiteral();
                    tokens.append(std::move(tok));
                    currentToken++;
                    return;
                }
                
                // Scan an operator Token.
                else if (TokenScannerHelper::isOperator(currentCharacter))
                {
                    if (currentCharacter == '(' && peekCharacter() == '*') {
                        Token tok = scanComment();
                        tokens.append(std::move(tok));
                        currentToken++;
                        return;
                    }
                    else {
                        Token tok = scanOperator();
                        tokens.append(std::move(tok));
                        currentToken++;
                        return;
                    }
                }
                
                else if (TokenScannerHelper::isWhiteSpace(currentCharacter))
                {
                    // Ignore white spaces.
                }
                
                else
                {
                    raiseError (String("Invalid Character."));
                }
                
                checkNewLine();
            }
            
            tokens.append(Token(Token::TypeEof, String(""), createPosition()));
            currentToken++;
        }
        
        Token EBNFScanner::scanIdentifier()
        {
            TokPosition pos = createPosition();
            char currchar   = getCurrentCharacter();
            String content  = String(&currchar, 1);
            CharArray _equals; _equals << '-' << '_';
            
            while (hasNextCharacter())
            {
                nextCharacter();
                
                // Ensure this character is in identifier.
                if(TokenScannerHelper::isAlphaNum(getCurrentCharacter()) ||
                   TokenScannerHelper::isEquals(getCurrentCharacter(), _equals) )
                {
                    content.append(getCurrentCharacter());
                }
                else
                {
                    backupCharacter();
                    break;
                }
            }
            
            return Token (TokIdentifier, content, pos);
        }
        
        Token EBNFScanner::scanLiteral()
        {
            TokPosition pos = createPosition();
            char _start = getCurrentCharacter();
            String content(&_start, 1);
            
            while (hasNextCharacter())
            {
                nextCharacter();
                content.append(getCurrentCharacter());
                
                // Ensure begin and end of literal.
                if(TokenScannerHelper::isQuote(getCurrentCharacter()) && getCurrentCharacter() == _start) {
                    break;
                }
            }
            
            return Token (TokLiteral, content, pos);
        }
        
        Token EBNFScanner::scanComment()
        {
        	char currchar   = getCurrentCharacter();
            TokPosition pos = createPosition();
            String content  = String(&currchar, 1);
            
            while (hasNextCharacter())
            {
                nextCharacter();
                content.append(getCurrentCharacter());
                
                if(getCurrentCharacter() == '*' && peekCharacter() == ')')
                {
                    nextCharacter();
                    content.append(getCurrentCharacter());
                    break;
                }
                
                checkNewLine();
            }
            
            return Token (TokComment, content, pos);
        }
        
        Token EBNFScanner::scanOperator()
        {
            TokPosition pos = createPosition();
            char currchar   = getCurrentCharacter();
            String content  = String(&currchar, 1);
            char peak       = peekCharacter();
            
            if(getCurrentCharacter() == ':' && peak == ':')
            {
                nextCharacter();
                content.append(getCurrentCharacter());
                nextCharacter();
                
                if(getCurrentCharacter() != '=') {
                    raiseError (String("Expecting '=' but got '") + getCurrentCharacter() + "' instead.");
                    content.append(getCurrentCharacter());
                    return Token (Token::TypeInvalid, content, pos);
                }
                
                content.append(getCurrentCharacter());
            }
            
            return Token (TokOperator, content, pos);
        }
        
        String EBNFScanner::GetUnquotedLiteral(const Token& literal)
        {
            if(literal.getType() == TokLiteral) {
                String result = literal.getContent();
                result.interpretastext();
                return result;
            }
            return literal.getContent();
        }
    }
    
    using namespace EBNF;

}
