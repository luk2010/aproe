////////////////////////////////////////////////////////////
/** @file TokenScanner.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/11/2014 - 07/02/2015
 *
 *  @brief
 *  Defines the TokenScanner class.
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
#ifndef APRO_TOKENSCANNER_H
#define APRO_TOKENSCANNER_H

#include "Platform.h"
#include "Array.h"
#include "SString.h"
#include "Pair.h"

#include "Swappable.h"

namespace APro
{
	/** @brief A generic Token Position.
	 *  First is the line number, Second is the column number.
	**/
	typedef Pair<int, int> TokPosition;
	
    ////////////////////////////////////////////////////////////
    /** @class Token
     *  @ingroup Utils
     *  @brief A generic Token class used by the Token Scanner.
     **/
    ////////////////////////////////////////////////////////////
    class Token : public Swappable<Token>
    {
    private:
        
        int         type;       ///< @brief The Token's type.
        String      content;    ///< @brief The content of this token.
        TokPosition position;   ///< @brief Position of the Token in the stream.
        
    public:
        
        Token (int tp, const String& cont, const TokPosition& pos);
        Token (const Token& tok);
        
        Token (Token&& tok);
        
        Token& operator = (Token tok);
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        void swap(Token& rhs);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the type of the Token. 
         *  @note This type is specific to the Scanner used.
        **/
        /////////////////////////////////////////////////////////////
        int getType() const { return type; }
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the content (or value) as a String.
        **/
        /////////////////////////////////////////////////////////////
        String& getContent() { return content; }
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the content (or value) as a String.
        **/
        /////////////////////////////////////////////////////////////
        const String& getContent() const { return content; }
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the position of the Token in the stream.
        **/
        /////////////////////////////////////////////////////////////
        const TokPosition& getPosition() const { return position; }
        
        enum CommonType
        {
            TypeInvalid = -1,
            TypeEof     = 0
        };
        
        static Token Invalid; ///< @brief An invalid Token. (Type is TypeInvalid)
    };
    
    typedef Array<Token> TokenArray;
    
    ////////////////////////////////////////////////////////////
    /** @class TokenScanner
     *  @ingroup Utils
     *  @brief Scan a stream and stores every encountered Tokens.
    **/
    ////////////////////////////////////////////////////////////
    class TokenScanner
    {
    protected:
        
        String  input;              ///< @brief Given string.
        int     inputLenght;        ///< @brief Lenght of the input.
        int     currentCharacter;   ///< @brief Current character position.
        int     currentToken;       ///< @brief Current token position.
        int     column;             ///< @brief Actual scanned column.
        int     line;               ///< @brief Actual scanned line.
        TokenArray tokens;          ///< @brief Collects every scanned token.
        
        typedef void (*OnSyntaxErrorCallBack) (const String&, int, int);
        OnSyntaxErrorCallBack syntaxerrorCallback; ///< @brief A error handling callback.
        
    public:
        
        TokenScanner (const String& str);
        virtual ~TokenScanner ();
        
    protected:
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns if there is a next character in the input
         *  String.
         **/
        /////////////////////////////////////////////////////////////
        bool hasNextCharacter() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Increments the character cursor.
         **/
        /////////////////////////////////////////////////////////////
        void nextCharacter();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the character at the current cursor position
         *  in the String.
         **/
        /////////////////////////////////////////////////////////////
        char getCurrentCharacter() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Decrements the character cursor of 1 position.
         **/
        /////////////////////////////////////////////////////////////
        void backupCharacter();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the next character without modifying the
         *  cursor position.
         **/
        /////////////////////////////////////////////////////////////
        char peekCharacter() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Call given callback to let user handle syntax
         *  errors.
         **/
        /////////////////////////////////////////////////////////////
        void raiseError(const String& msg);
        
        /////////////////////////////////////////////////////////////
        /** @brief Creates a TokPosition structure from current line
         *  and column.
        **/
        /////////////////////////////////////////////////////////////
        TokPosition createPosition() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Checks if the current character is a new line 
         *  character ('\n' or '\r'), increments the line counter ans
         *  reset the column counter.
        **/
        /////////////////////////////////////////////////////////////
        void checkNewLine();
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Set the callback to handle Syntax Error.
         **/
        /////////////////////////////////////////////////////////////
        void setSyntaxErrorCallback(OnSyntaxErrorCallBack cbck);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the current scanned token.
         **/
        /////////////////////////////////////////////////////////////
        Token& getCurrentToken();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the current scanned token.
         **/
        /////////////////////////////////////////////////////////////
        const Token& getCurrentToken() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the nth token backwards from the actual
         *  token.
         **/
        /////////////////////////////////////////////////////////////
        Token& backtrackToken(int cnt = 1);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the nth token backwards from the actual
         *  token.
         **/
        /////////////////////////////////////////////////////////////
        const Token& backtrackToken(int cnt = 1) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if there are more tokens.
         **/
        /////////////////////////////////////////////////////////////
        bool hasNextToken() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the next token without advancing the internal
         *  token cursor.
         **/
        /////////////////////////////////////////////////////////////
        Token& peekToken();
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Start the scanning of the next token.
         **/
        /////////////////////////////////////////////////////////////
        virtual void nextToken() = 0;
    };
}

#endif
