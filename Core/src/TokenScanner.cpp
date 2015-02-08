////////////////////////////////////////////////////////////
/** @file TokenScanner.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/11/2014 - 07/02/2014
 *
 *  @brief
 *  Implements the TokenScanner class.
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
#include "TokenScanner.h"

namespace APro
{
    Token Token::Invalid = Token (Token::TypeInvalid, String(""), Token::TokPosition(0,0));
    
    Token::Token (int tp, const String& cont, const Token::TokPosition& pos)
    {
        type     = tp;
        content  = cont;
        position = pos;
    }
    
    Token::Token (const Token& tok)
    {
        type     = tok.type;
        content  = tok.content;
        position = tok.position;
    }

    Token::Token (Token&& tok)
    {
        type     = stdmove(tok.type);
        content  = stdmove(tok.content);
        position = stdmove(tok.position);
        
        tok.type     = -1;
        tok.content.clear();
        tok.position = TokPosition (0,0);
    }
    
    void Token::swap(Token& rhs)
    {
        using std::swap;
        
        swap(type,     rhs.type);
        swap(content,  rhs.content);
        swap(position, rhs.position);
    }
    
    Token& Token::operator = (Token tok)
    {
        swap (*this, tok);
        return *this;
    }
    
    
    TokenScanner::TokenScanner (const String& str)
    {
        input            = str;
        inputLenght      = str.size();
        currentCharacter = -1;
        currentToken     = -1;
        column           = 0;
        line             = 1;
        syntaxErrorCallback = nullptr;
    }
    
    TokenScanner::~TokenScanner ()
    {
        
    }
    
    bool TokenScanner::hasNextCharacter () const
    {
        return currentCharacter < inputLenght - 1;
    }
    
    void TokenScanner::nextCharacter ()
    {
        currentCharacter++;
        column++;
    }
    
    char TokenScanner::getCurrentCharacter () const
    {
        return input.at(currentCharacter);
    }
    
    void TokenScanner::backupCharacter ()
    {
        currentCharacter--;
        column--;
    }
    
    char TokenScanner::peekCharacter () const
    {
        if(hasNextCharacter())
            return input.at(currentCharacter + 1);
        return 0;
    }
    
    void TokenScanner::raiseError (const String& msg)
    {
        if (syntaxErrorCallback)
            syntaxErrorCallback (msg, line, column);
    }
    
    TokenScanner::TokPosition TokenScanner::createPosition()
    {
        return TokPosition (line, column);
    }
    
    void TokenScanner::checkNewLine()
    {
        if(currentCharacter == '\n' || currentCharacter == '\r')
        {
            line++;
            column = 0;
        }
    }
    
    void TokenScanner::setSyntaxErrorCallback (TokenScanner::OnSyntaxErrorCallback cbck)
    {
        syntaxErrorCallback = cbck;
    }
    
    Token& TokenScanner::getCurrentToken()
    {
        if(tokens.exists(currentToken))
            return tokens[currentToken];
        
        return Token::Invalid;
    }
    
    const Token& TokenScanner::getCurrentToken() const
    {
        if(tokens.exists(currentToken))
            return tokens[currentToken];
        
        return Token::Invalid;
    }
    
    Token& TokenScanner::backtrackToken(int cnt)
    {
        cnt = currentToken - cnt;
        if(tokens.exists(cnt))
            return tokens[cnt];
        
        raiseError(String("Can't get backtracked Token at index '") + String::toString(cnt) + String("'."));
        return Token::Invalid;
    }
    
    const Token& TokenScanner::backtrackToken(int cnt) const
    {
        cnt = currentToken - cnt;
        if(tokens.exists(cnt))
            return tokens[cnt];
        
        raiseError(String("Can't get backtracked Token at index '") + String::toString(cnt) + String("'."));
        return Token::Invalid;
    }
    
    bool TokenScanner::hasNextToken() const
    {
        return getCurrentToken().getType() != Token::TypeEof;
    }
    
    Token& TokenScanner::peekToken()
    {
        nextToken();
        currentToken--;
        
        if(currentToken < 0)
            currentToken = 0;
        return tokens[currentToken + 1];
    }
}
